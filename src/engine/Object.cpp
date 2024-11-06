#include "Object.h"
#include "Utility.h"
namespace staywalk{
	Object::Object(const string& name)
		:guid_(Utility::get_random_id()), name_(name) {
	}
	
	Object::Object(idtype load_id, const string& name)
		: guid_(load_id), name_(name){
	}

	void Object::dump_impl(ofstream& ofs, Dumper& dumper){
		Utility::write_to_stream(guid_, ofs);
		Utility::write_to_stream(name_, ofs);
	}

	void Object::load_impl(shared_ptr<Object> obj, ifstream& ifs, Loader& loader){
		obj->guid_ = Utility::load_from_stream<idtype>(ifs);
		obj->name_ = Utility::load_from_stream<string>(ifs);
	}
}