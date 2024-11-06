#pragma once
#include "Common.h"


namespace staywalk{
	class Dumper;
	class Loader;

	template<typename T>
	class DumpLoad {
	public:
		void dump(ofstream& ofs, Dumper& dumper);
		static shared_ptr<T> load(ifstream& ifs, Loader& loader);
	};

	enum class ObjectType : uint {
		Object,
		GameObject,
		Actor,
		StaticMeshComponent,
		Camera,
	};

	class Object : public DumpLoad<Object> {
	public:
		Object(const string& name = "0-obj");
		Object(idtype load_id, const string& name = "0-obj");
		virtual ~Object() = default;

		Object(const Object&) = delete;
		Object(Object&&) = delete;
		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;

		//virtual Object clone() {}
		//virtual Object deep_clone() {}
		idtype get_guid() { return guid_; }
		void set_name(const string& str) { name_ = str; }
		string get_name() { return name_; }
		virtual ObjectType get_type_value() { return ObjectType::Object; }  // must override


		bool operator==(const Object& rhs) {
			return guid_ == rhs.guid_ && name_ == rhs.name_;
		}
	protected:
		void dump_impl(ofstream& ofs, Dumper& dumper);
		static void load_impl(shared_ptr<Object> obj, ifstream& ifs, Loader& loader);
		
		idtype guid_;
		string name_{"0-obj"};
	};


}

namespace staywalk {
	template<typename T>
	void DumpLoad<T>::dump(ofstream& ofs, Dumper& dumper) {
		this->T::dump_impl(ofs, dumper);
	}

	template<typename T>
	shared_ptr<T> DumpLoad<T>::load(ifstream& ifs, Loader& loader) {
		auto result = std::make_shared<T>();
		T::load_impl(result, ifs);
		return result;
	}
}

