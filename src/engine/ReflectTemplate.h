#pragma once

namespace staywalk {

	enum class ObjectType : unsigned int {
		None,
		Object,
	};

	template<typename T, typename Super>
	class Serializer {
	public:

		//static ObjectType get_type_value()  { static_assert(false && "Not impl"); }
		//static bool operator==(const T& lhs, const T& rhs) {static_assert(false && "Not impl");}

		//static void dump(const T& obj, ofstream& ofs, Dumper& dumper) { static_assert(false && "Not impl"); }
		//static void load(T& obj, ifstream& ifs, Loader& loader) { static_assert(false && "Not impl"); }
	};
}


#include "Actor.h"
#include "Utility.h"
//
//ObjectType get_type_value() const override { return ObjectType::Actor; }
//bool operator==(const Actor& gameobj);
//	protected:
//		void dump_impl(ofstream& ofs, Dumper& dumper) const override;
//		void load_impl(ifstream& ifs, Loader& loader) override;

namespace staywalk {
	//template<>
	//ObjectType Serializer<Object, void>::get_type_value() { return ObjectType::Object; }

	//template<>
	//bool Serializer<Object, void>::operator==(const Object& lhs, const Object& rhs) {
	//	//return GameObject::operator==(rhs) &&
	//		return Utility::equal(lhs.guid_, rhs.guid_);
	//}

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