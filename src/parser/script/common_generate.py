from parse_class import ClassNode, NoClassField, get_sw_labels
import clang.cindex
import os
from mylog import *
from pathlib import Path
import common

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

# ---------------create enum table start------------------
enum_info_code1 = '''
template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<{cur_type}>() {{
    return {{ '''

enum_info_code2 = '''
        {{static_cast<int>({enum_value}), "{enum_str}"}},'''

enum_info_code_end = '''
    };
}'''

enum_info_declare = '''
template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<{cur_type}>();'''

# ---------------create enum table end------------------


class CommonBind(object):
    def __init__(self, bind_node):
        self._base_names = None
        self._node = bind_node._node
        self.outer_classes = [x.spelling for x in bind_node._outer_classes]
        self._namespaces = [x.spelling for x in bind_node._namespaces]
        self._name = self._node.spelling
        self._full_name = '::' + '::'.join(self._namespaces) + '::' + '::'.join(
            self.outer_classes) + self._node.spelling
        self._props = []

    @property
    def name(self):
        return self._name

    @property
    def fullname(self):
        return self._full_name

    @property
    def header(self):
        p = Path(str(self._node.extent.start.file.name)).as_posix().replace(common.src_path, '')
        return p


class EnumBind(CommonBind):
    def __init__(self, bind_node: NoClassField):
        super().__init__(bind_node)
        self._parse()

    def _enum_info_code(self):
        code = ''
        code += enum_info_code1.format(cur_type=self._full_name)
        for prop in self._props:
            code += enum_info_code2.format(enum_value=self._full_name + '::' + prop, enum_str=prop)
        code += enum_info_code_end
        declare = enum_info_declare.format(cur_type=self._full_name)
        return declare, code

    def generate_code(self):
        declare, impl = self._enum_info_code()
        return declare, impl

    def _parse(self):
        find_base = [base.spelling for base in self._node.get_children() if
                     base.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER]
        self._base_names = find_base[0] if len(find_base) > 0 else None

        for member in self._node.get_children():
            if member.kind != clang.cindex.CursorKind.ENUM_CONSTANT_DECL:
                continue
            self._props.append(member.spelling)


def generate(nodes: list[ClassNode], enums: list[NoClassField],  reflect_dir):
    generate_dir = os.path.join(reflect_dir, 'generated')
    common_target_file = os.path.join(generate_dir, 'Common.gen.h')
    common_imp_target_file = os.path.join(generate_dir, 'Common.gen.cpp')
    logging.log(logging.INFO, f'generate serialize code to {common_target_file}, {common_imp_target_file} ...')

    include_code = '#include "{}"'
    all_include_code = ''
    create_code = ''

    for node in nodes:
        if not node.labeled():
            continue
        labels = get_sw_labels(node._node)
        if 'nojson' in labels:
            continue
        snode = CommonBind(node)  # 只是使用了文件头
        logging.log(logging.INFO, f'start generate {node._node.spelling}')
        all_include_code += include_code.format(snode.header) + '\n'
        create_code += create_obj_code2.format(cur_type_str=snode.fullname[2:], cur_type=snode.fullname)

    enum_code_declare = ''
    enum_code_impl = ''
    for e in enums:
        if not e.labeled():
            continue

        snode = EnumBind(e)
        logging.log(logging.INFO, f'start generate {snode.fullname}')
        all_include_code += include_code.format(snode.header) + '\n'
        declare, impl = snode.generate_code()
        enum_code_declare += declare + '\n'
        enum_code_impl += impl + '\n'
        print('-------------->', snode.fullname)

    with open(common_imp_target_file, 'w') as common:
        common.write(all_include_code + '\n\n\n')
        common.write(include_code.format(os.path.join('reflect', 'reflect.h')))
        common.write(create_obj_code1)
        common.write(create_code)
        common.write(create_obj_code3)
        common.write(create_obj_code4)
        common.write('\n\n')
        common.write(enum_code_impl)

    with open(common_target_file, 'w') as common:
        common.write('#pragma once\n\n')
        common.write('namespace staywalk{ namespace reflect{\n\tenum class ObjectType : unsigned int{\n')
        type_count = 0
        for node in nodes:
            if not node.labeled():
                continue
            common.write('\t\t' + node.name + ', \n')
            type_count += 1

        common.write('}; }}')
        common.write('\n\n')
        common.write(f'constexpr int kObjectTypeCount = {type_count};\n\n')
        common.write(enum_code_declare)
        common.write('\n\n')

