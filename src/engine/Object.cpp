#include "Object.h"
#include "Utility.h"
namespace staywalk{
	Object::Object(const string& name)
		:guid_(Utility::get_random_id()), name_(name) {
	}
	
	Object::Object(idtype load_id, const string& name)
		: guid_(load_id), name_(name){
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
		obj->guid_ = Utility::load_from_stream<idtype>(ifs);
		obj->name_ = Utility::load_from_stream<string>(ifs);
	}
}