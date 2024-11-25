import sys
import os

import clang.cindex
from parse_class import ClassNode, NoClassField
from parse import traverse, display_traverse
import serialize_generate
import ui_generate
import common_generate
import py_bind_generate

if __name__ == '__main__':
    print('===============start up parse for reflect=================')
    code_src_path = ''
    if len(sys.argv) > 1:
        print('Usage: python startup.py [include-directory]')
        code_src_path = sys.argv[1]
    code_src_path = R'C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src'
    if not os.path.isdir(code_src_path):
        print(f'Wrong src directory {code_src_path}')
        exit(0)

    other_path = os.path.join(code_src_path, '..', '3rdparty')
    other_include_path = list()
    other_include_path.append('-I{}/assimp/include'.format(other_path))
    other_include_path.append('-I{}/cpython/build/Include'.format(other_path))
    other_include_path.append('-I{}/fmt/include'.format(other_path))
    other_include_path.append('-I{}/glfw/include'.format(other_path))
    other_include_path.append('-I{}/glm'.format(other_path))
    other_include_path.append('-I{}/imgui'.format(other_path))
    other_include_path.append('-I{}/opengl/include'.format(other_path))
    other_include_path.append('-I{}/pybind11/include'.format(other_path))
    other_include_path.append('-I{}/rapidjson/include'.format(other_path))
    other_include_path.append('-I{}/stb'.format(other_path))

    print(f'current path: {os.getcwd()}')
    print(f'include directory is {code_src_path}')
    index = clang.cindex.Index.create()
    compile_args = [
                       '-std=c++17',
                       '-I{}/engine'.format(code_src_path),
                       # f'-I{code_src_path}/reflect',
                       '-D_IN_REFLECT=1',  # switch on reflect
                   ] + other_include_path

    s_node = index.parse(f"{code_src_path}/engine/ReflectEntry.cpp",
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
    py_bind_generate.generate(result, os.path.join(code_src_path, 'reflect'))
    common_generate.generate(result, enums, os.path.join(code_src_path, 'reflect'))
    print('===============end up parse for reflect  =================')
