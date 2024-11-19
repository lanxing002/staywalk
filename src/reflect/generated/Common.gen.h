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
}; }}


template<>
std::vector<std::pair<int, std::string>> staywalk::reflect::get_enum_label<staywalk::ShaderType>() {
	return { 
		{static_cast<int>(staywalk::ShaderType::CS), "CS"},
		{static_cast<int>(staywalk::ShaderType::CS), "FS"}
	};
}