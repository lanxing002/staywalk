#pragma once

#include "RProgram.h"
#include "RenderInfo.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "Camera.h"
#include "RProgram.h"
#include "RenderObject.h"
namespace staywalk{ namespace reflect{
	enum class ObjectType : unsigned int{
		Object, 
		GameObject, 
		Actor, 
		RObject, 
		Tex2D, 
		CubeMap, 
		Shader, 
		Uniform, 
		Program, 
		Material, 
		Camera, 
		RLight, 
		Utility, 
		Engine, 
		World, 
		GameComponent, 
		Mesh, 
		SkeletonMesh, 
		StaticMeshComponent, 
		Terrain, 
		BoneTreeNode, 
		Animation, 
		SkeletonMeshComponent, 
}; }}

constexpr int kObjectTypeCount = 23;


template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::UniformType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ProgramType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlMagFilter>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlMinFilter>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ProjectType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ShaderType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlWrap>();


