import sys
import os

import clang.cindex
from parse_class import ClassNode, BindClass, NoClassField
from parse import traverse

if __name__ == '__main__':
    print('===============start up parse for reflect=================')
    print(os.getcwd())


    code_src_path = sys.argv[1]
    print(f'include direcory is {code_src_path}')
    index = clang.cindex.Index.create()
    compile_args = [
        f'-I{code_src_path}/engine',
        '-D_IN_REFLECT=1',  # switch on reflect
    ]

    s_node = index.parse(f"{code_src_path}/engine/main.cpp",
                         compile_args)
    namespaces = []
    outer_classes = []
    result: set[ClassNode] = set()
    noclass_fields: set[NoClassField] = set()
    traverse(s_node.cursor, namespaces, outer_classes, result, noclass_fields, 0)

    for item in result:
        if item.labeled():
            print(item)

    for item in noclass_fields:
        if item.labeled():
            print(item)

    print('===============end up parse for reflect  =================')

