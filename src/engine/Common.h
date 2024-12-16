#pragma once
#include "stdcommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
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
	constexpr uint kGlSickId = 0;
	static constexpr uint kMaxBoueInfluence = 4;
	static constexpr uint kMaxBoneNum = 100;

	namespace reflect {
		template<typename T>
		class Serializer;
		struct MetaInfo;
		class Dumper;
		class Loader;
	}
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

#define GLCheck(__invoke_code)\
	__invoke_code; Utility::check_gl_error(fmt::format("flie: {} --> line: {}", __FILE__, __LINE__));

// forward declare 
namespace staywalk{
	class BoneTreeNode;
	class BoneInfo;
	class Bone;
	class SkinVertex;
	
	class World;
	class Object;
	class Entity;
	class Actor;
	class Component;
	class StaticMeshComponent;
	class SkeletonMeshComponent;
	class SkeletonMesh;
	
	class RObject;
	class Program;
	class Shader;
	class Material;
	class RLight;
	class Camera;
	class Tex2D;
	class CubeMap;
	class Mesh;
	class Uniform;
	class Animation;

	using WorldRef  = shared_ptr<World>;
	using ObjectRef = shared_ptr<Object>;
	using EntityRef = shared_ptr<Entity>;
	using ActorRef = shared_ptr<Actor>;
	using ComponentRef = shared_ptr<Component>;
	using StaticMeshComponentRef = shared_ptr<StaticMeshComponent>;
	using SkeletonMeshComponentRef = shared_ptr<SkeletonMeshComponent>;
	using AnimationRef = shared_ptr<Animation>;
	using SkeletonMeshRef = shared_ptr<SkeletonMesh>;

	using ProgramRef = shared_ptr<Program>;
	using ShaderRef = shared_ptr<Shader>;
	using MaterialRef = shared_ptr<Material>;
	using LightRef = shared_ptr<RLight>;
	using TexRef = shared_ptr<Tex2D>;
	using CubeMapRef = shared_ptr<CubeMap>;
	using MeshRef = shared_ptr<Mesh>;
	using UniformRef = shared_ptr<Uniform>;

	using CameraRef = shared_ptr<Camera>;

	class Engine;
}