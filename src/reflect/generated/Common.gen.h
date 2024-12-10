#pragma once

#include "Camera.h"
#include "RProgram.h"
#include "RenderInfo.h"
#include "RProgram.h"
#include "RenderObject.h"
#include "RenderObject.h"
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
		StaticMeshComponent, 
		Terrain, 
}; }}

constexpr int kObjectTypeCount = 19;


template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ProjectType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::UniformType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ProgramType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ShaderType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlMagFilter>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlWrap>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlMinFilter>();


