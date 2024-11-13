#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\Object.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::Object>::dump(const ::staywalk::Object& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::Object>::load(::staywalk::Object& obj, ifstream& ifs, Loader& loader); 
#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\GameObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::GameObject>::dump(const ::staywalk::GameObject& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::GameObject>::load(::staywalk::GameObject& obj, ifstream& ifs, Loader& loader); 
#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\GameComponent.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::GameComponent>::dump(const ::staywalk::GameComponent& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::GameComponent>::load(::staywalk::GameComponent& obj, ifstream& ifs, Loader& loader); 
#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::RObject>::dump(const ::staywalk::RObject& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::RObject>::load(::staywalk::RObject& obj, ifstream& ifs, Loader& loader); 
#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::RTex>::dump(const ::staywalk::RTex& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::RTex>::load(::staywalk::RTex& obj, ifstream& ifs, Loader& loader); 
#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::RMesh>::dump(const ::staywalk::RMesh& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::RMesh>::load(::staywalk::RMesh& obj, ifstream& ifs, Loader& loader); 
#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::Resource>::dump(const ::staywalk::Resource& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::Resource>::load(::staywalk::Resource& obj, ifstream& ifs, Loader& loader); 
#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::Shader>::dump(const ::staywalk::Shader& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::Shader>::load(::staywalk::Shader& obj, ifstream& ifs, Loader& loader); 
#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\StaticMeshComponent.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::StaticMeshComponent>::dump(const ::staywalk::StaticMeshComponent& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::StaticMeshComponent>::load(::staywalk::StaticMeshComponent& obj, ifstream& ifs, Loader& loader); 
#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\Actor.h"

template<>
void ::staywalk::reflect::Serializer<::staywalk::Actor>::dump(const ::staywalk::Actor& obj, ofstream& ofs, Dumper& dumper);
template<>
void ::staywalk::reflect::Serializer<::staywalk::Actor>::load(::staywalk::Actor& obj, ifstream& ifs, Loader& loader); 
