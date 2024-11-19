import sys
import os

import clang.cindex
from parse_class import ClassNode, BindClass, NoClassField
from parse import traverse, display_traverse
import serialize_generate
import ui_generate
import common_generate

if __name__ == '__main__':
    print('===============start up parse for reflect=================')
    if len(sys.argv) < 2:
        print('Usage: python startup.py [include-directory]')
        exit(0)

    code_src_path = sys.argv[1]
    # code_src_path = R'C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src'
    if not os.path.isdir(code_src_path):
        print(f'Wrong src directory {code_src_path}')

    print(f'current path: {os.getcwd()}')
    print(f'include directory is {code_src_path}')
    index = clang.cindex.Index.create()
    compile_args = [
        f'-I{code_src_path}/engine',
        # f'-I{code_src_path}/reflect',
        '-D_IN_REFLECT=1',  # switch on reflect
    ]

    s_node = index.parse(f"{code_src_path}/engine/main.cpp",
                         compile_args)
    namespaces = []
    outer_classes = []
    result: list[ClassNode] = []
    noclass_fields: set[NoClassField] = set()
    traverse(s_node.cursor, namespaces, outer_classes, result, noclass_fields, 0)
    # display_traverse(s_node.cursor, 0)
    enums = list(filter(lambda x: x.is_enum(), noclass_fields))
    serialize_generate.generate(result, os.path.join(code_src_path, 'reflect'))
    ui_generate.generate(result, os.path.join(code_src_path, 'reflect'))
    ui_generate.generate(result, os.path.join(code_src_path, 'reflect'))
    common_generate.generate(result, enums, os.path.join(code_src_path, 'reflect'))
    print('===============end up parse for reflect  =================')

