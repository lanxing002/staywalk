import logging

from parse_class import ClassNode, NoClassField, get_sw_labels
import os
from mylog import *
import clang.cindex


class FuncParam:
    def __init__(self):
        self.param_ts = []
        self.param_names = []
        self.param_defaults = []

    def append_arg(self, param_t, param_name, param_default=None):
        self.param_ts.append(param_t)
        self.param_names.append(param_name)
        self.param_defaults.append(param_default)


class BindClass(object):

    def __init__(self, bind_node: ClassNode):
        self._node = bind_node.node
        self._name = self._node.spelling
        self._base_names = []
        self.outer_classes = [x.spelling for x in bind_node.outer_classes]
        self._namespaces = [x.spelling for x in bind_node.namespaces]
        self._constructors: list[FuncParam] = []
        self._funcs = []
        self._members = []
        self._static_members = []
        self._full_name = '::' + '::'.join(self._namespaces) + '::' + '::'.join(
            self.outer_classes) + self._node.spelling

        self._parse()

    @property
    def name(self):
        return self._name

    @property
    def full_name(self):
        return self._full_name

    @property
    def header(self):
        return str(self._node.extent.start.file.name)

    def __repr__(self):
        result = f'''py::class_<{self.full_name}{','.join([''] + self._base_names)}, std::shared_ptr<{self.full_name}>>(__module, "{self.name}")\n'''
        for cons in self._constructors:
            result += f'''\t.def(py::init<{','.join([x for x in cons.param_ts])}>())\n'''

        funcs_dict = {}
        for f in self._funcs:
            r = funcs_dict.get(f[0], [])
            r.append(f)
            funcs_dict[f[0]] = r

        for key, value in funcs_dict.items():
            if len(value) == 1:
                name, _, is_pointer, is_static = value[0]
                def_s = 'def_static' if is_static else 'def'
                result += f'''\t.{def_s}("{name}", &{self._name}::{name}{', py::return_value_policy::reference' if is_pointer else ''})\n'''
            elif len(value) > 1:
                for name, params, is_pointer, is_static in value:
                    def_s = 'def_static' if is_static else 'def'
                    overload_str = f'''py::overload_cast<{','.join(params.param_ts)}>'''
                    result += f'''\t.{def_s}("{name}", {overload_str}(&{self._name}::{name}){', py::return_value_policy::reference' if is_pointer else ''})\n'''

        # for func, is_pointer in self._funcs:
        #     result += f'''\t.def("{func}", &{self._name}::{func}{', py::return_value_policy::reference' if is_pointer else ''})\n'''
        result += ';'
        return result

    def __str__(self):
        return self.__repr__()

    @staticmethod
    def _parse_parameters(node):
        result = FuncParam()
        for arg in node.get_arguments():
            param_type = arg.type.spelling
            param_name = arg.spelling
            result.append_arg(param_type, param_name)
        print(str(node.spelling) + '-----')
        print(result)
        return result

    def generate_code(self):
        # code = '''PYBIND11_MODULE(crown, __module){{\n{bind_code}\n}}'''
        # return code.format(bind_code=self.__repr__())
        return self.__repr__()

    def _parse(self):
        self._base_names = [base.spelling for base in self._node.get_children() if
                        base.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER]

        for member in self._node.get_children():
            labels = [str(m.spelling) for m in member.get_children() if m.kind == clang.cindex.CursorKind.ANNOTATE_ATTR]
            if len(labels) == 0:
                continue
            assert len(labels) == 1
            labels = labels[0].split(';')
            labels = [s.strip() for s in labels]
            assert [0] != '__sw'

            if 'nopy' in labels:
                logging.log(logging.INFO, "nogui for this property : {}".format(member.spelling))
                continue

            if member.access_specifier == clang.cindex.AccessSpecifier.PUBLIC:
                if member.kind == clang.cindex.CursorKind.CONSTRUCTOR:
                    cons = BindClass._parse_parameters(member)
                    self._constructors.append(cons)
                elif member.kind == clang.cindex.CursorKind.FIELD_DECL:
                    self._members.append(member.spelling)
                elif member.kind == clang.cindex.CursorKind.CXX_METHOD:
                    return_type = member.result_type
                    is_pointer = return_type.kind == clang.cindex.TypeKind.POINTER
                    params = BindClass._parse_parameters(member)
                    self._funcs.append((member.spelling, params, is_pointer, member.is_static_method()))
                    #
                    # if member.is_static_method():
                    #     self._static_funcs.append((member.spelling, params, is_pointer))
                    # else:
                    #     self._funcs.append((member.spelling, params, is_pointer))
                elif member.kind == clang.cindex.CursorKind.VAR_DECL and member.storage_class == clang.cindex.StorageClass.STATIC:
                    self._static_members.append(member.spelling)


def generate(nodes: list[ClassNode], reflect_dir):
    generate_dir = os.path.join(reflect_dir, 'generated')
    declare_target_file = os.path.join(generate_dir, 'ScriptBindAll.gen.h')
    impl_target_file = os.path.join(generate_dir, 'ScriptBindAll.gen.cpp')
    logging.log(logging.INFO, f'generate serialize code to {declare_target_file}, {impl_target_file} ...')
    include_code = '#include "{}"\n'
    with open(declare_target_file, 'w') as decl:
        with open(impl_target_file, 'w') as impl:
            impl.write(include_code.format(os.path.join(reflect_dir, 'Script.h')))
            impl.write('namespace py = pybind11;\n')
            impl.write('using namespace staywalk;\n')

            bind_classes = []

            for node in nodes:
                if not node.labeled():
                    continue
                bind_classes.append(BindClass(node))
            [impl.write(include_code.format(x.header)) for x in bind_classes]
            impl.write('\n\n')

            module_code = '''PYBIND11_MODULE(staywalk, __module){{\n{bind_code}\n}}'''
            bind_code = ''
            for bind_obj in bind_classes:
                logging.log(logging.INFO, f'start generate {bind_obj.name}')
                bind_code += bind_obj.generate_code() + '\n\n'
                # decl_code, impl_code = snode.generate_code()
                # impl.write(include_code.format(snode.header) + '\n')
                # impl.write(str(bind_obj) + '\n')
                # decl.write(decl_code + '\n')
            impl.write(module_code.format(bind_code=bind_code))
            impl.write('\n')
            impl.write('''void ::staywalk::reflect::py_bind() { PyImport_AppendInittab("staywalk", PyInit_staywalk);} ''')
            impl.write('\n\n')

