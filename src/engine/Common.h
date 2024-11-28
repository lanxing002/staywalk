#pragma once
#include "stdcommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "rapidjson/document.h"

#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <array>
#include <filesystem>
#include <cassert>
#include <set>

#ifdef _IN_REFLECT
#define sw_Prop(...) __attribute__((annotate("__sw;" #__VA_ARGS__)))
#define sw_Func(...) __attribute__((annotate("__sw;" #__VA_ARGS__)))
#define sw_Class(...) __attribute__((annotate("__sw;" #__VA_ARGS__)))
#elif __INTELLISENSE__
#define sw_Prop(...)   
#define sw_Func(...)   
#define sw_Class(...)  
#else
#define sw_Prop(...)   
#define sw_Func(...)   
#define sw_Class(...)
#endif // _IN_REFLECT

namespace staywalk
{
	using idtype = uint64_t;

	using vec2 = glm::vec2;
	using vec3 = glm::vec3;
	using vec4 = glm::vec4;
	using mat4 = glm::mat4;
	using quat = glm::quat;

	template<typename T>
	using shared_ptr = std::shared_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using vector = std::vector<T>;

	template<typename TKey, typename TVal>
	using map = std::map<TKey, TVal>;

	template<typename TKey, typename TVal>
	using pair = std::pair<TKey, TVal>;

	template<typename TKey>
	using set = std::set<TKey>;

	template<typename T, typename VT>
	using hashtable = std::unordered_map<T, VT>;

	template<typename T, std::size_t S>
	using array = std::array<T, S>;
	
	using string = std::string;

	using ifstream = std::ifstream;
	using ofstream = std::ofstream;
	using uint = unsigned int;

	template<typename T1, typename T2>
	std::shared_ptr<T1> pcast(std::shared_ptr<T2> other) {
		return std::dynamic_pointer_cast<T1>(other);
	}

	namespace fs = std::filesystem;

	constexpr idtype kInvalidId = -1;
	constexpr uint kGlSickId = -1;

	namespace reflect {
		template<typename T>
		class Serializer;
		struct MetaInfo;
		class Dumper;
		class Loader;
	}

	struct Transform {
		vec3 location ;
		vec3 scale;
		quat rotation ;

		bool operator==(const Transform& rhs) const {
			return location == rhs.location &&
				scale == rhs.scale &&
				rotation == rhs.rotation;
		}

		void dump(rapidjson::Value&, staywalk::reflect::Dumper&) const;

		void load(rapidjson::Value&, staywalk::reflect::Loader&);
	};

	constexpr static Transform Identity = Transform{vec3(.0), vec3(1.0), quat(0.0, .0, .0, 1.0)};
}

#define __MetaRegisterBase(TypeName)													\
public:																			\
	bool operator==(const TypeName&) const;										\
	friend class staywalk::reflect::Serializer<TypeName>;						\
	virtual staywalk::reflect::MetaInfo get_meta_info() const;					\
	virtual void dump(rapidjson::Value&, staywalk::reflect::Dumper&) const;		\
	virtual void load(rapidjson::Value&, staywalk::reflect::Loader&);			\
	virtual void construct_basic_ui(bool can_modify);							\
	virtual void construct_obj_ui(bool can_modify);								

#define MetaRegister(TypeName)													\
public:																			\
	bool operator==(const TypeName&) const;										\
	friend class staywalk::reflect::Serializer<TypeName>;						\
	staywalk::reflect::MetaInfo get_meta_info() const override;					\
	void dump(rapidjson::Value&, staywalk::reflect::Dumper&) const override;	\
	void load(rapidjson::Value&, staywalk::reflect::Loader&) override;			\
	void construct_basic_ui(bool can_modify) override;							\
	void construct_obj_ui(bool can_modify) override;								
	//virtual void construct_ui();	

