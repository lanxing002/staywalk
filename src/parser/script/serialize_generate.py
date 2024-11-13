from parse_class import ClassNode, NoClassField, FuncParam
import clang.cindex
import os
from mylog import *

# --------------dump code start-----------------
dump_code1 = '''
template<>
void ::staywalk::reflect::Serializer<{cur_type}>::dump(const {cur_type}& obj, ofstream& ofs, Dumper& dumper) {{'''

dump_code2 = '''
    Serializer<{base_type}>::dump(obj, ofs, dumper);'''

dump_code3 = '''
    dumper.write(obj.{dump_prop}, ofs);'''

dump_code4 = '''
}
'''

dump_declare = '''
template<>
void ::staywalk::reflect::Serializer<{cur_type}>::dump(const {cur_type}& obj, ofstream& ofs, Dumper& dumper);'''
# --------------dump code end-----------------


# --------------load code start-----------------
load_code1 = '''
template<>
void ::staywalk::reflect::Serializer<{cur_type}>::load({cur_type}& obj, ifstream& ifs, Loader& loader) {{'''

load_code2 = '''
    Serializer<{base_type}>::load(obj, ifs, loader);'''

load_code3 = '''
    loader.read(obj.{load_prop}, ifs);'''

load_code4 = '''
}
'''

load_declare = '''
template<>
void ::staywalk::reflect::Serializer<{cur_type}>::load({cur_type}& obj, ifstream& ifs, Loader& loader);'''
# --------------load code end-----------------


# ---------------operator == code start------------------
eop_code1 = '''
bool {cur_type}::operator==(const {cur_type}& rhs){{'''

eop_code2 = '''
    return 
'''

eop_code3 = '''{base_type}::operator==(rhs) '''

eop_code4 = '''::staywalk::Comparer::equal(this->{load_prop}, rhs.{load_prop})'''

eop_code5 = '''
}
'''

eop_declare = ''' '''


# ---------------operator == code end------------------

class SerializeBind(object):
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
    def header(self):
        return str(self._node.extent.start.file.name)

    def _dump_code(self):
        code = ''
        code += dump_code1.format(cur_type=self._full_name)
        code += dump_code2.format(base_type=self._base_names) if self._base_names else ''
        for p in self._props:
            code += dump_code3.format(dump_prop=p)
        code += dump_code4
        declare = dump_declare.format(cur_type=self._full_name)
        return declare, code

    def _load_code(self):
        code = ''
        code += load_code1.format(cur_type=self._full_name)
        code += load_code2.format(base_type=self._base_names) if self._base_names else ''
        for p in self._props:
            code += load_code3.format(load_prop=p)
        code += load_code4
        declare = load_declare.format(cur_type=self._full_name)
        return declare, code

    def _eop_code(self):
        code = ''
        code += eop_code1.format(cur_type=self._full_name)
        code += eop_code2
        code += eop_code3.format(base_type=self._base_names) if self._base_names else 'true'
        for p in self._props:
            code += ' && ' + eop_code4.format(load_prop=p)
        code += ';'
        code += eop_code5
        declare = eop_declare.format(cur_type=self._full_name)
        return declare, code

    def generate_code(self):
        ns_code = '{func_code}'
        for ns in self._namespaces[::-1]:
            ns_code = 'namespace ' + ns + '{{' + ns_code + '}}'
        declare1, impl1 = self._dump_code()
        declare2, impl2 = self._load_code()
        declare3, impl3 = self._eop_code()
        return declare1 + declare2 + declare3, impl1 + '\n' + impl2 + '\n' + impl3

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


def generate(nodes: list[ClassNode], reflect_dir):
    generate_dir = os.path.join(reflect_dir, 'generated')
    declare_target_file = os.path.join(generate_dir, 'SerializeAll.gen.h')
    impl_target_file = os.path.join(generate_dir, 'SerializeAll.gen.cpp')
    logging.log(logging.INFO, f'generate serialize code to {declare_target_file}, {impl_target_file} ...')

    include_code = '#include "{}"'

    with open(declare_target_file, 'w') as decl:
        with open(impl_target_file, 'w') as impl:
            impl.write(include_code.format(os.path.join(reflect_dir, 'Serialize.h')))
            for node in nodes:
                if not node.labeled():
                    continue
                snode = SerializeBind(node)
                logging.log(logging.INFO, f'start generate {node._node.spelling}')
                decl_code, impl_code = snode.generate_code()
                decl.write(include_code.format(snode.header) + '\n')
                decl.write(decl_code + '\n')
                impl.write(impl_code + '\n')
