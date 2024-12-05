#pragma once

#include "Camera.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RProgram.h"
#include "RenderObject.h"
#include "RenderInfo.h"
namespace staywalk{ namespace reflect{
	enum class ObjectType : unsigned int{
		Object, 
		GameObject, 
		Actor, 
		Resource, 
		Tex2d, 
		RObject, 
		RTex, 
		RShader, 
		RUniform, 
		RProgram, 
		Material, 
		Camera, 
		Light, 
		Engine, 
		World, 
		GameComponent, 
		Mesh, 
		StaticMeshComponent, 
}; }}

constexpr int kObjectTypeCount = 18;


template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ProjectType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlMinFilter>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlMagFilter>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ShaderType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlWrap>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ProgramType>();


