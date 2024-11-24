#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src\reflect\Script.h"
namespace py = pybind11;
using namespace staywalk;
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Object.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\GameObject.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\GameComponent.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Material.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RMesh.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\StaticMeshComponent.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Actor.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Camera.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Light.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\World.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Engine.h"


PYBIND11_MODULE(staywalk, __module){
py::class_<::staywalk::Object, std::shared_ptr<::staywalk::Object>>(__module, "Object")
	.def(py::init<const string &>())
;

py::class_<::staywalk::GameObject,Object, std::shared_ptr<::staywalk::GameObject>>(__module, "GameObject")
	.def(py::init<const string &>())
;

py::class_<::staywalk::GameComponent,Object, std::shared_ptr<::staywalk::GameComponent>>(__module, "GameComponent")
	.def(py::init<const string &>())
;

py::class_<::staywalk::Resource,Object, std::shared_ptr<::staywalk::Resource>>(__module, "Resource")
	.def(py::init<const string &>())
;

py::class_<::staywalk::Shader,Resource, std::shared_ptr<::staywalk::Shader>>(__module, "Shader")
;

py::class_<::staywalk::Tex2d,Resource, std::shared_ptr<::staywalk::Tex2d>>(__module, "Tex2d")
;

py::class_<::staywalk::RObject,Object, std::shared_ptr<::staywalk::RObject>>(__module, "RObject")
	.def(py::init<const string &>())
;

py::class_<::staywalk::RTex,RObject, std::shared_ptr<::staywalk::RTex>>(__module, "RTex")
;

py::class_<::staywalk::RShader,RObject, std::shared_ptr<::staywalk::RShader>>(__module, "RShader")
;

py::class_<::staywalk::RProgram,RObject, std::shared_ptr<::staywalk::RProgram>>(__module, "RProgram")
;

py::class_<::staywalk::RUniform,RObject, std::shared_ptr<::staywalk::RUniform>>(__module, "RUniform")
;

py::class_<::staywalk::Material,Object, std::shared_ptr<::staywalk::Material>>(__module, "Material")
	.def(py::init<shared_ptr<RShader>,const string &>())
	.def("add_tex", &Material::add_tex)
	.def("add_uniform", &Material::add_uniform)
;

py::class_<::staywalk::RMesh,RObject, std::shared_ptr<::staywalk::RMesh>>(__module, "RMesh")
	.def(py::init<const string &>())
	.def(py::init<const vector<Vertex> &,const vector<unsigned int> &,const string &>())
;

py::class_<::staywalk::StaticMeshComponent,GameComponent, std::shared_ptr<::staywalk::StaticMeshComponent>>(__module, "StaticMeshComponent")
	.def(py::init<const string &>())
;

py::class_<::staywalk::Actor,GameObject, std::shared_ptr<::staywalk::Actor>>(__module, "Actor")
	.def(py::init<const string &>())
;

py::class_<::staywalk::Camera,GameObject, std::shared_ptr<::staywalk::Camera>>(__module, "Camera")
	.def(py::init<const string &>())
;

py::class_<::staywalk::Light,GameObject, std::shared_ptr<::staywalk::Light>>(__module, "Light")
	.def(py::init<const string &>())
;

py::class_<::staywalk::World, std::shared_ptr<::staywalk::World>>(__module, "World")
	.def_static("create_empty_world", &World::create_empty_world)
	.def_static("load_marry_world", &World::load_marry_world)
	.def_static("load", &World::load)
	.def("get_actors", &World::get_actors)
	.def("get_cameras", &World::get_cameras)
	.def("get_lights", &World::get_lights)
	.def("add_actor", &World::add_actor)
	.def("remove_actor", py::overload_cast<shared_ptr<Actor>>(&World::remove_actor))
	.def("remove_actor", py::overload_cast<idtype>(&World::remove_actor))
	.def("get_name", &World::get_name)
	.def("set_name", &World::set_name)
;

py::class_<::staywalk::Engine, std::shared_ptr<::staywalk::Engine>>(__module, "Engine")
	.def_static("get_engine", &Engine::get_engine)
	.def_static("get_world", &Engine::get_world)
	.def_static("set_world", &Engine::set_world)
	.def_static("get_console", &Engine::get_console)
	.def("load_world", &Engine::load_world)
	.def("select", &Engine::select)
	.def("get_selected", &Engine::get_selected)
;


}
void ::staywalk::reflect::py_bind() { PyImport_AppendInittab("staywalk", PyInit_staywalk);} 

