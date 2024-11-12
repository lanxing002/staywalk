import clang.cindex
NodeT = clang.cindex.Cursor


class NoClassField:
    def __init__(self, node: NodeT, namespaces: list[NodeT]) -> None:
        self._node = node
        self._namespaces = namespaces
        pass

    def labeled(self) -> bool:
        if not self._node:
            return False
        for child in self._node.get_children():
            if child.kind == clang.cindex.CursorKind.ANNOTATE_ATTR  and str(child.spelling).startswith('__sw'):
                return True
        return False

    def __str__(self):
        return self.__repr__()

    def __repr__(self):
        return f'''{self._node.spelling}: {'::'.join([x.spelling for x in self._namespaces])}'''

    def __hash__(self):
        return hash(self.__repr__())

    def __eq__(self, other):
        return self.__repr__() == other.__repr__()

class ClassNode:
    def __init__(self, node: NodeT, namespaces: list[NodeT], outer_classes: list[NodeT]):
        self._node = node
        self._namespaces = namespaces
        self._outer_classes = outer_classes
        pass

    @property
    def name(self):
        return self._node.spelling

    @property
    def node(self):
        return self._node

    @property
    def namespaces(self):
        return self._namespaces

    @property
    def outer_classes(self):
        return self._outer_classes

    def labeled(self) -> bool:
        if not self._node:
            return False
        for child in self._node.get_children():
            if child.kind == clang.cindex.CursorKind.ANNOTATE_ATTR and str(child.spelling).startswith('__sw'):
                return True
        return False

    def __str__(self):
        return self.__repr__()

    def __repr__(self):
        return f'''{self._node.spelling}: {'::'.join([x.spelling for x in self._namespaces])}, {'::'.join([x.spelling for x in self._outer_classes])}'''

    def __hash__(self):
        return hash(self.__repr__())

    def __eq__(self, other):
        return self.__repr__() == other.__repr__()


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
        self._static_funcs = []
        self._static_members = []

        self._parse()

    @property
    def name(self):
        return self._name

    def __repr__(self):
        result = f'''py::class_<{'::'.join(self._namespaces)}::{self._name}{','.join([''] + self._base_names)}>(__module, "{self._name}")\n'''
        for cons in self._constructors:
            result += f'''\t.def(py::init<{','.join([x for x in cons.param_ts])}>())\n'''

        funcs_dict = {}
        for f in self._funcs:
            r = funcs_dict.get(f[0], [])
            r.append(f)
            funcs_dict[f[0]] = r

        for key, value in funcs_dict.items():
            if len(value) == 1:
                name, _, is_pointer = value[0]
                result += f'''\t.def("{name}", &{self._name}::{name}{', py::return_value_policy::reference' if is_pointer else ''})\n'''
            elif len(value) > 1:
                for name, params, is_pointer in value:
                    overload_str = f'''py::overload_cast<{','.join(params.param_ts)}>'''
                    result += f'''\t.def("{name}", {overload_str}(&{self._name}::{name}){', py::return_value_policy::reference' if is_pointer else ''})\n'''

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

        return result

    def _parse(self):
        self._base_names = [base.spelling for base in self._node.get_children() if
                        base.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER]

        for member in self._node.get_children():
            if member.access_specifier == clang.cindex.AccessSpecifier.PUBLIC:
                if member.kind == clang.cindex.CursorKind.CONSTRUCTOR:
                    cons = BindClass._parse_parameters(member)
                    self._constructors.append(cons)
                elif member.kind == clang.cindex.CursorKind.FIELD_DECL:
                    print(member.spelling)
                    self._members.append(member.spelling)
                elif member.kind == clang.cindex.CursorKind.CXX_METHOD:
                    return_type = member.result_type
                    is_pointer = return_type.kind == clang.cindex.TypeKind.POINTER
                    params = BindClass._parse_parameters(member)
                    if member.is_static_method():
                        self._static_funcs.append((member.spelling, params, is_pointer))
                    else:
                        self._funcs.append((member.spelling, params, is_pointer))
                elif member.kind == clang.cindex.CursorKind.VAR_DECL and member.storage_class == clang.cindex.StorageClass.STATIC:
                    self._static_members.append(member.spelling)

