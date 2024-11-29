import clang.cindex
NodeT = clang.cindex.Cursor


def get_sw_labels(cnode: NodeT):
    labels = [str(m.spelling) for m in cnode.get_children() if m.kind == clang.cindex.CursorKind.ANNOTATE_ATTR]
    if len(labels) == 0:
        return []
    labels = labels[0].split(';')
    labels = [s.strip() for s in labels]
    return labels



class NoClassField:
    def __init__(self, node: NodeT, namespaces: list[NodeT], outer_classes: list[NodeT]) -> None:
        self._node = node
        self._namespaces = namespaces
        self._outer_classes = outer_classes
        pass

    def labeled(self) -> bool:
        if not self._node:
            return False
        for child in self._node.get_children():
            if child.kind == clang.cindex.CursorKind.ANNOTATE_ATTR and str(child.spelling).startswith('__sw'):
                return True
        return False

    @property
    def full_name(self) -> str:
        return '::' + '::'.join(self._namespaces) + '::' + '::'.join(self.outer_classes) + self._node.spelling

    def is_enum(self):
        return self._node.kind == clang.cindex.CursorKind.ENUM_DECL

    def is_definition(self):
        return self._node.is_definition()

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

    def is_definition(self):
        return self._node.is_definition()

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


