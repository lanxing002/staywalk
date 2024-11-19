from parse_class import ClassNode, NoClassField, FuncParam
import clang.cindex
import os
from mylog import *

# ---------------create code start------------------
create_obj_code1 = '''
using namespace staywalk;
shared_ptr<Object> reflect::create_empty(reflect::MetaInfo minfo) {
    if (false) { return nullptr; }
'''

create_obj_code2 = '''
    else if (minfo.tname == "{cur_type_str}"){{return std::make_shared<{cur_type}>();}}
'''

create_obj_code3 = '''
    else {assert(false); return nullptr;}
'''

create_obj_code4 = '''
}
'''
# ---------------create code end------------------


class CommonBind(object):
    def __init__(self, bind_node: ClassNode):
        self._node = bind_node.node
        self._base_names = None
        self.outer_classes = [x.spelling for x in bind_node.outer_classes]
        self._namespaces = [x.spelling for x in bind_node.namespaces]
        self._name = self._node.spelling
        self._full_name = '::' + '::'.join(self._namespaces) + '::' + '::'.join(
            self.outer_classes) + self._node.spelling
        self._props = []
        self._parse()

    @property
    def name(self):
        return self._name

    @property
    def fullname(self):
        return self._full_name

    @property
    def header(self):
        return str(self._node.extent.start.file.name)

    def _typeo_code(self):
        code = ''
        code += typeo_code1.format(cur_type=self._full_name[2:])
        code += typeo_code2.format(cur_type_enum=self._full_name[2:])
        code += typeo_code3
        return typeo_declare, code

    def generate_code(self):
        ns_code = '{func_code}'
        for ns in self._namespaces[::-1]:
            ns_code = 'namespace ' + ns + '{{' + ns_code + '}}'

        declare, impl = self._typeo_code()
        return declare, impl

    def _parse(self):
        find_base = [base.spelling for base in self._node.get_children() if
                     base.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER]
        self._base_names = find_base[0] if len(find_base) > 0 else None

        for member in self._node.get_children():
            if member.kind != clang.cindex.CursorKind.FIELD_DECL:
                continue

            is_label = filter(lambda x: x.kind == clang.cindex.CursorKind.ANNOTATE_ATTR and
                                        str(x.spelling).startswith('__sw'), member.get_children())
            is_label = len(list(is_label)) > 0
            if not is_label:
                continue

            self._props.append(member.spelling)


def generate(nodes: list[ClassNode], reflect_dir):
    generate_dir = os.path.join(reflect_dir, 'generated')
    common_target_file = os.path.join(generate_dir, 'Common.gen.h')
    common_imp_target_file = os.path.join(generate_dir, 'Common.gen.cpp')
    logging.log(logging.INFO, f'generate serialize code to {common_target_file}, {common_imp_target_file} ...')

    include_code = '#include "{}"'

    with open(common_target_file, 'w') as common:
        common.write('namespace staywalk{ namespace reflect{\n\tenum class ObjectType : unsigned int{\n')
        for node in nodes:
            if not node.labeled():
                continue
            common.write('\t\t' + node.name + ', \n')
        common.write('}; }}')


    all_include_code = ''
    create_code = ''
    for node in nodes:
        if not node.labeled():
            continue
        snode = CommonBind(node)
        logging.log(logging.INFO, f'start generate {node._node.spelling}')
        all_include_code += include_code.format(snode.header) + '\n'
        create_code += create_obj_code2.format(cur_type_str=snode.fullname[2:], cur_type=snode.fullname)

    with open(common_imp_target_file, 'w') as common:
        common.write(all_include_code + '\n\n\n')
        common.write(include_code.format(os.path.join(reflect_dir, 'reflect.h')))
        common.write(create_obj_code1)
        common.write(create_code)
        common.write(create_obj_code3)
        common.write(create_obj_code4)

