#pragma once
#include "Common.h"


namespace staywalk{
	class Dumper;
	class Loader;

	enum class ObjectType : uint {
		Object,
		GameObject,
		Actor,
		GameComponent,
		StaticMeshComponent,
		Camera,
		Material,
		RObject,
		RTex,
		RMesh,
		RShader,
		RProgram,
		RUniform,
		
		Resource, 
		Tex2d,
		Shader,

	};

	class Object {
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
		idtype get_guid() const { return guid_; }
		void set_name(const string& str) { name_ = str; }
		string get_name() const { return name_; }
		
		virtual ObjectType get_type_value() const { return ObjectType::Object; }  // must override
		inline bool operator==(const Object& rhs) const {
			return guid_ == rhs.guid_ && name_ == rhs.name_;
		}

	protected:
		virtual void dump_impl(ofstream& ofs, Dumper& dumper) const;
		virtual void load_impl(ifstream& ifs, Loader& loader);
		
		idtype guid_;
		string name_{"0-obj"};

		friend class Dumper;
		friend class Loader;
	};
}



