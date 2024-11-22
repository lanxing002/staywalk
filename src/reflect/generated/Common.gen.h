#pragma once

namespace staywalk{ namespace reflect{
	enum class ObjectType : unsigned int{
		Object, 
		GameObject, 
		GameComponent, 
		Resource, 
		Shader, 
		Tex2d, 
		RObject, 
		RTex, 
		RShader, 
		RProgram, 
		RUniform, 
		Material, 
		RMesh, 
		StaticMeshComponent, 
		Actor, 
		Camera, 
		Light, 
}; }}


template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ShaderType>();


