import sys

import clang.cindex
from parse_class import ClassNode, BindClass, NoClassField

def traverse(root, namespace, outer_class, classes, noclass_fields, depth):
    print("%s%s %s" % ("|   " * depth, str(root.kind), root.spelling))

    # depth first visit
    for n in root.get_children():
        if root.kind == clang.cindex.CursorKind.NAMESPACE:
            namespace.append(root)
            traverse(n, namespace, outer_class, classes, noclass_fields, depth + 1)

            if n.kind == clang.cindex.CursorKind.ENUM_DECL \
                    or n.kind == clang.cindex.CursorKind.VAR_DECL \
                    or n.kind == clang.cindex.CursorKind.FUNCTION_DECL:
                noclass_fields.add(NoClassField(n, [x for x in namespace]))

            namespace.pop()
        elif root.kind == clang.cindex.CursorKind.CLASS_DECL:
            ins = ClassNode(root, [x for x in namespace], [x for x in outer_class])
            if not (len(namespace) > 0 and namespace[0].spelling == 'std'):
                classes.add(ins)
            outer_class.append(root)
            traverse(n, namespace, outer_class, classes, noclass_fields, depth + 1)
            outer_class.pop()
        else:
            traverse(n, namespace, outer_class, classes, noclass_fields, depth + 1)


if __name__ == '__main__':
    code_src_path = sys.argv[1]

    index = clang.cindex.Index.create()
    compile_args = [
        f'-I{code_src_path}/engine',
        '-D_IN_REFLECT=1',  # switch on reflect
    ]

    s_node = index.parse(R"C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src\parser\script\test.cpp",
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