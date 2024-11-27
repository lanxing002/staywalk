import logging

from parse_class import ClassNode, NoClassField, get_sw_labels
import clang.cindex
import os
from mylog import *
from enum import Enum

# --------------dump code start-----------------
bind_basic_func_code = '''
void {cur_type}::construct_basic_ui(bool can_modify) {{'''

bind_base_basic = '''
    {base_type}::construct_basic_ui(can_modify);'''

bind_basic = '''
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype({prop})>()) 
        staywalk::reflect::UIHelper::construct_ui("{prop}", {prop}, can_modify || {can_modify});'''

bind_obj_func_code = '''
void {cur_type}::construct_obj_ui(bool can_modify) {{'''

bind_base_obj = '''
    {base_type}::construct_obj_ui(can_modify);'''

bind_obj = '''
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype({prop})>()){{ 
        //if (ImGui::TreeNode("{prop}")){{
            staywalk::reflect::UIHelper::construct_ui("{prop}", {prop}, can_modify || {can_modify});
            //ImGui::TreePop();
        //}}    
    }}'''

bind_end_code = '''
}
'''

# ---------------create code end------------------


class Accessor(Enum):
    PUBLIC = 0
    PROTECTED = 1
    PRIVATE = 2


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
        for p, accessor in self._props:
            code += bind_basic.format(prop=p, can_modify='true' if accessor == Accessor.PUBLIC else 'false')
        code += bind_end_code
        code += '\n\n'

        code += bind_obj_func_code.format(cur_type=self._full_name)
        code += bind_base_obj.format(base_type=self._base_names) if self._base_names else ''
        for p, accessor in self._props:
            code += bind_obj.format(prop=p, can_modify='true' if accessor == Accessor.PUBLIC else 'false')
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

            labels = [str(m.spelling) for m in member.get_children() if m.kind == clang.cindex.CursorKind.ANNOTATE_ATTR]
            if len(labels) == 0:
                continue
            assert len(labels) == 1
            labels = labels[0].split(';')
            labels = [s.strip() for s in labels]
            assert [0] != '__sw'

            if 'nogui' in labels:
                logging.log(logging.INFO, "nogui for this property : {}".format(member.spelling))
                continue

            accessor = None
            accessor = Accessor.PUBLIC if member.access_specifier == clang.cindex.AccessSpecifier.PUBLIC else accessor
            accessor = Accessor.PROTECTED if member.access_specifier == clang.cindex.AccessSpecifier.PROTECTED else accessor
            accessor = Accessor.PRIVATE if member.access_specifier == clang.cindex.AccessSpecifier.PRIVATE else accessor
            self._props.append((member.spelling, accessor))


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

            labels = get_sw_labels(node._node)
            if 'nogui' in labels:
                continue

            snode = UIHelper(node)
            logging.log(logging.INFO, f'start generate ui code for {node._node.spelling}')
            _, impl_code = snode.generate_code()
            impl.write(include_code.format(snode.header) + '\n')
            impl.write(impl_code + '\n')

