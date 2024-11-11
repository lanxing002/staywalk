import clang.cindex
from parse_class import ClassNode, BindClass


def traverse(node, ns, oc, classes, depth):
    print("%s%s %s" % ("|   " * depth, str(node.kind), node.spelling))
    if node.kind == clang.cindex.CursorKind.ANNOTATE_ATTR:
        print('-------------------', node)

    for n in node.get_children():
        if node.kind == clang.cindex.CursorKind.NAMESPACE:
            ns.append(node)
            traverse(n, ns, oc, classes, depth + 1)
            ns.pop()
        elif node.kind == clang.cindex.CursorKind.CLASS_DECL:
            ins = ClassNode(node, [x for x in ns], [x for x in oc])
            if not (len(ns) > 0 and ns[0].spelling == 'std'):
                classes.add(ins)
            oc.append(node)
            traverse(n, ns, oc, classes, depth + 1)
            oc.pop()
        else:
            traverse(n, ns, oc, classes, depth + 1)


if __name__ == '__main__':
    index = clang.cindex.Index.create()
    compile_args = [
                    '-IC:\\Users\\lanxi\\Documents\\lanxing\\codes\\ErJiu\\staywalk\\src\\engine',
                    '-DOSG_EXPORT=',
                    '-DOSGVIEWER_EXPORT=',
                    '-fsyntax-only',
                    '-D__GNUC__=7'
                    ]

    s_node = index.parse(R"C:\Users\lanxi\Documents\lanxing\codes\ErJiu\staywalk\src\parser\test.cpp",
                       compile_args)
    namespaces = []
    outer_classes = []
    result: set[ClassNode] = set()
    traverse(s_node.cursor, namespaces, outer_classes, result, 0)

    for item in result:
        print(BindClass(item))

