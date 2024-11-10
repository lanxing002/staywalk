#include "Object.h"
#include "Utility.h"
namespace staywalk{
	Object::Object(const string& name)
		:guid_(Utility::get_random_id()), name_(name) {
	}
	
	Object::Object(idtype load_id, const string& name)
		: guid_(load_id), name_(name){
	}

	void Object::dump_impl(ofstream& ofs, Dumper& dumper) const {
		dumper.write_basic(guid_, ofs);
		dumper.write_basic(name_, ofs);
	}

	void Object::load_impl(ifstream& ifs, Loader& loader){
		guid_ = loader.read_basic<idtype>(ifs);
		name_ = loader.read_basic<string>(ifs);
	}
}