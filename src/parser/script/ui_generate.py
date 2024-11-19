from parse_class import ClassNode, NoClassField, FuncParam
import clang.cindex
import os
from mylog import *


# --------------dump code start-----------------
bind_basic_func_code = '''
void {cur_type}::construct_basic_ui() {{'''

bind_base_basic = '''
    {base_type}::construct_basic_ui();'''

bind_basic = '''
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype({prop})>()) 
        staywalk::reflect::UIHelper::construct_ui("{prop}", {prop});'''

bind_obj_func_code = '''
void {cur_type}::construct_obj_ui() {{'''

bind_base_obj = '''
    {base_type}::construct_obj_ui();'''

bind_obj = '''
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype({prop})>()) 
        staywalk::reflect::UIHelper::construct_ui("{prop}", {prop});'''

bind_end_code = '''
}
'''

# ---------------create code end------------------


class UIHelper(object):
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

    def generate_code(self):
        code = ''
        code += bind_basic_func_code.format(cur_type=self._full_name)
        code += bind_base_basic.format(base_type=self._base_names) if self._base_names else ''
        for p in self._props:
            if p == 'guid_':
                continue
            code += bind_basic.format(prop=p)
        code += bind_end_code
        code += '\n\n'

        code += bind_obj_func_code.format(cur_type=self._full_name)
        code += bind_base_obj.format(base_type=self._base_names) if self._base_names else ''
        for p in self._props:
            if p == 'guid_':
                continue
            code += bind_obj.format(prop=p)
        code += bind_end_code
        code += '\n\n'

        return '', code


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
    declare_target_file = os.path.join(generate_dir, 'UIBindAll.gen.h')
    impl_target_file = os.path.join(generate_dir, 'UIBindAll.gen.cpp')
    logging.log(logging.INFO, f'generate ui bind code to {declare_target_file}, {impl_target_file} ...')

    include_code = '#include "{}"'

    with open(impl_target_file, 'w') as impl:
        impl.write(include_code.format(os.path.join(reflect_dir, 'ConstructUI.h')))
        impl.write('\n')
        for node in nodes:
            if not node.labeled():
                continue
            snode = UIHelper(node)
            logging.log(logging.INFO, f'start generate ui code for {node._node.spelling}')
            _, impl_code = snode.generate_code()
            impl.write(include_code.format(snode.header) + '\n')
            impl.write(impl_code + '\n')

