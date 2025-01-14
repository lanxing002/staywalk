#pragma once

#include "RenderObject.h"
#include "Light.h"
#include "Camera.h"
#include "RProgram.h"
#include "RenderInfo.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RProgram.h"
#include "RenderObject.h"
namespace staywalk{ namespace reflect{
	enum class ObjectType : unsigned int{
		Object, 
		Entity, 
		Actor, 
		RObject, 
		Tex, 
		Tex2D, 
		Tex2DRT, 
		FrameBuffer, 
		CubeMap, 
		Shader, 
		Uniform, 
		Program, 
		StateSet, 
		Material, 
		Camera, 
		RLight, 
		Utility, 
		Engine, 
		World, 
		Component, 
		Mesh, 
		SkeletonMesh, 
		StaticMeshComponent, 
		Terrain, 
		BoneTreeNode, 
		Animation, 
		SkeletonMeshComponent, 
		RenderTarget, 
		DepthRenderTarget, 
		Skybox, 
}; }}

constexpr int kObjectTypeCount = 30;


template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlWrap>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::LightType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ProjectType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ShaderType>();

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
staywalk::reflect::get_enum_label<::staywalk::UniformType>();

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlTexFormat>();


