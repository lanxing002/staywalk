#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Object.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::Object>::dump(const ::staywalk::Object& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::Object>::load(::staywalk::Object& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\GameObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::GameObject>::dump(const ::staywalk::GameObject& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::GameObject>::load(::staywalk::GameObject& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\GameComponent.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::GameComponent>::dump(const ::staywalk::GameComponent& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::GameComponent>::load(::staywalk::GameComponent& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::RObject>::dump(const ::staywalk::RObject& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::RObject>::load(::staywalk::RObject& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::RTex>::dump(const ::staywalk::RTex& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::RTex>::load(::staywalk::RTex& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::RShader>::dump(const ::staywalk::RShader& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::RShader>::load(::staywalk::RShader& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::RProgram>::dump(const ::staywalk::RProgram& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::RProgram>::load(::staywalk::RProgram& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::RUniform>::dump(const ::staywalk::RUniform& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::RUniform>::load(::staywalk::RUniform& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::Resource>::dump(const ::staywalk::Resource& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::Resource>::load(::staywalk::Resource& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::Shader>::dump(const ::staywalk::Shader& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::Shader>::load(::staywalk::Shader& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::Tex2d>::dump(const ::staywalk::Tex2d& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::Tex2d>::load(::staywalk::Tex2d& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Material.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::Material>::dump(const ::staywalk::Material& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::Material>::load(::staywalk::Material& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RMesh.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::RMesh>::dump(const ::staywalk::RMesh& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::RMesh>::load(::staywalk::RMesh& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\StaticMeshComponent.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::StaticMeshComponent>::dump(const ::staywalk::StaticMeshComponent& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::StaticMeshComponent>::load(::staywalk::StaticMeshComponent& obj, ifstream& ifs, Loader& loader);  
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Actor.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::Actor>::dump(const ::staywalk::Actor& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::Actor>::load(::staywalk::Actor& obj, ifstream& ifs, Loader& loader);  