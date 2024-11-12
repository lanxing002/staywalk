from parse_class import ClassNode, NoClassField, FuncParam
import clang.cindex
import os
from mylog import *

dump_code1 = '''
template<>
void staywalk::reflect::Serializer<{cur_type}>::dump(const {cur_type}& obj, ofstream& ofs, Dumper& dumper) {{'''

dump_code2 = '''
    Serializer<{base_type}>::dump(obj, ofs, dumper);'''

dump_code3 = '''
    dumper.write(obj.{dump_prop}, ofs);'''

dump_code4 = '''
}
'''


load_code1 = '''
template<>
void staywalk::reflect::Serializer<{cur_type}>::load({cur_type}& obj, ifstream& ifs, Loader& loader) {{'''

load_code2 = '''
    Serializer<{base_type}>::load(obj, ifs, loader);'''

load_code3 = '''
    loader.read(obj.{load_prop}, ifs);'''

load_code4 = '''
}
'''


class SerializeBind(object):
    def __init__(self, bind_node: ClassNode):
        self._node = bind_node.node
        self._base_names = None
        self.outer_classes = [x.spelling for x in bind_node.outer_classes]
        self._namespaces = [x.spelling for x in bind_node.namespaces]
        self._name = self._node.spelling
        self._full_name = '::'.join(self._namespaces) + '::' + '::'.join(self.outer_classes) + self._node.spelling
        self._props = []
        self._parse()

    @property
    def name(self):
        return self._name

    def _dump_code(self):
        code = ''
        code += dump_code1.format(cur_type=self._name)
        code += dump_code2.format(base_type=self._base_names) if self._base_names else ''
        for p in self._props:
            code += dump_code3.format(dump_prop=p)
        code += dump_code4
        return code

    def _load_code(self):
        code = ''
        code += load_code1.format(cur_type=self._name)
        code += load_code2.format(base_type=self._base_names) if self._base_names else ''
        for p in self._props:
            code += load_code3.format(load_prop=p)
        code += load_code4
        return code

    def __repr__(self):
        ns_code = '{func_code}'
        for ns in self._namespaces[::-1]:
            ns_code = 'namespace ' + ns + '{{' + ns_code + '}}'
        code = self._dump_code() + '\n' + self._load_code()
        return ns_code.format(func_code=code)

    def __str__(self):
        return self.__repr__()

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


code_t = \
    '''
#pragma once
#include "Common.gen.h"

{include_list}

namespace staywalk {
namespace reflect{
	template<typename T, typename Super>
	class Serializer {
	public:
		static bool operator==(const T& lhs, const T& rhs) {static_assert(false && "Not impl");}
		static void dump(const T& obj, ofstream& ofs, Dumper& dumper) { static_assert(false && "Not impl"); }
		static void load(T& obj, ifstream& ifs, Loader& loader) { static_assert(false && "Not impl"); }
	};
}
}

namespace staywalk {
namespace reflect{
	//template<>
	//bool Serializer<Object, void>::operator==(const Object& lhs, const Object& rhs) {
	//	//return GameObject::operator==(rhs) &&
	//		return Utility::equal(lhs.guid_, rhs.guid_);
	//}


	//@object_impl

	//template<>
	//ObjectType Serializer<Object, void>::get_type_value() { return ObjectType::Object; }

	//void Serializer<Object, void>::dump(const Object& obj, ofstream& ofs, Dumper& dumper) {
	//	dumper.write_basic(obj.guid_, ofs);
	//}
	//void Serializer<Actor, GameObject>::load(Actor& obj, ifstream& ifs, Loader& loader) { 
	//	obj.sm_comp_ = std::dynamic_pointer_cast<StaticMeshComponent>(loader.read_nested_obj(ifs)); // TODO:
	//}

	//void Serializer<Actor, GameObject>::dump(const Actor& obj, ofstream& ifs, Dumper& loader) {
	//	obj.sm_comp_ = std::dynamic_pointer_cast<StaticMeshComponent>(loader.read_nested_obj(ifs)); // TODO:
	//}

	////void Actor::dump_impl(ofstream& ofs, Dumper& dumper) const {
	////	GameObject::dump_impl(ofs, dumper);
	////	dumper.write_nested_obj(sm_comp_, ofs);
	////}

	//void Actor::load_impl(ifstream& ifs, Loader& loader) {
	//	GameObject::load_impl(ifs, loader);
	//	sm_comp_ = std::dynamic_pointer_cast<StaticMeshComponent>(loader.read_nested_obj(ifs)); // TODO:
	//}
}
}

'''


def generate(nodes: list[ClassNode], generate_dir):
    target_file = os.path.join(generate_dir, 'SerializeAll.gen.h')
    logging.log(logging.INFO, f'generate serialize code to {target_file} ...')
    with open(target_file, 'w') as f:
        for node in nodes:
            if not node.labeled():
                continue
            snode = SerializeBind(node)
            logging.log(logging.INFO, f'start generate {node._node.spelling}')
            f.write(str(snode))
            f.write('\n\n\n')
