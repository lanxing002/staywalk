
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