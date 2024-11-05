#include "Object.h"
#include "Utility.h"
namespace staywalk{
	Object::Object() 
		:guid_(Utility::get_random_id()){
	}

	Object::Object(idtype load_id)
		: guid_(load_id){
	}

	void Object::dump(ofstream& ofs, Dumper& dumper){
		if (!Utility::check_ofstream(ofs)) return;
		Utility::write_to_stream(guid_, ofs);
		Utility::write_to_stream(name_, ofs);
	}

	shared_ptr<Object> Object::load(ifstream& ifs, Loader& loader){
		if (!Utility::check_ifstream(ifs)) return nullptr;
		auto result = std::make_shared<Object>();
		result->placement_load(result, ifs);
		return result;
	}

	void Object::placement_load(shared_ptr<Object> obj, ifstream& ifs){
		if (!Utility::check_ifstream(ifs)) return;

		idtype rid;
		ifs.read(reinterpret_cast<char*>(&rid), sizeof guid_);
		obj->guid_ = rid;
	}
}