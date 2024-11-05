#pragma once
#include "Common.h"

namespace staywalk{
	class Dumper;
	class Loader;

	enum class ObjectType : uint {
		Object,
		GameObject,
		Actor,
		StaticMeshComponent,
		Camera,
	};

	class Object{
	public:
		Object();

		Object(const string& name) : name_(name) {}

		Object(idtype load_id);

		Object(const Object&) = delete;
		Object(Object&&) = delete;
		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;

		//virtual Object clone() {}
		//virtual Object deep_clone() {}
		idtype get_guid() { return guid_; }

		bool operator==(const Object& rhs) {
			return guid_ == rhs.guid_;
		}

		void set_name(const string& str) { name_ = str; }
		string get_name() { return name_; }

		virtual void dump(ofstream& ofs, Dumper& dumper);
		static shared_ptr<Object> load(ifstream& ifs, Loader& loader);
		
		virtual ObjectType get_type_value() { return ObjectType::Object; }  // must override

		virtual ~Object() = default;

	protected:
		static void placement_load(shared_ptr<Object> obj, ifstream& ifs);
		idtype guid_;
		string name_{"default"};
	};


}

