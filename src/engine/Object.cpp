#include "Object.h"
#include "Utility.h"
namespace staywalk{
	Object::Object() 
		:guid_(Utility::GetRandomId()){
	}

	Object::Object(long long load_id)
		: guid_(load_id){
	}

	void Object::dump(ofstream& ofs){
		if (!Utility::check_ofstream(ofs)) return;
		ofs.write(reinterpret_cast<char*>(&guid_), sizeof guid_);
	}

	shared_ptr<Object> Object::load(ifstream& ifs){
		if (!Utility::check_ifstream(ifs)) return nullptr;
		auto result = std::make_shared<Object>();
		result->placement_load(result, ifs);
		return result;
	}

	void Object::placement_load(shared_ptr<Object> obj, ifstream& ifs){
		if (!Utility::check_ifstream(ifs)) return;

		long long rid;
		ifs.read(reinterpret_cast<char*>(&rid), sizeof guid_);
		obj->guid_ = rid;
	}
}