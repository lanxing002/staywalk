#include "Script.h"
namespace py = pybind11;
using namespace staywalk;
#include "Object.h"
#include "GameObject.h"
#include "Actor.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RProgram.h"
#include "RProgram.h"
#include "RProgram.h"
#include "Material.h"
#include "Camera.h"
#include "Light.h"
#include "Utility.h"
#include "Engine.h"
#include "World.h"
#include "GameComponent.h"
#include "RMesh.h"
#include "StaticMeshComponent.h"
#include "Terrain.h"


static void bind_auto(py::module& __module){
py::class_<::staywalk::Object, std::shared_ptr<::staywalk::Object>>(__module, "Object")
	.def(py::init<const string &>())
	.def_readwrite("name", &Object::name)
;

py::class_<::staywalk::GameObject,Object, std::shared_ptr<::staywalk::GameObject>>(__module, "GameObject")
	.def(py::init<const string &>())
	.def_readwrite("transform", &GameObject::transform)
;

py::class_<::staywalk::Actor,GameObject, std::shared_ptr<::staywalk::Actor>>(__module, "Actor")
	.def(py::init<const string &>())
	.def("get_aabb", &Actor::get_aabb)
	.def_readwrite("sm_comp", &Actor::sm_comp)
;

py::class_<::staywalk::Resource,Object, std::shared_ptr<::staywalk::Resource>>(__module, "Resource")
	.def(py::init<const string &>())
	.def_readwrite("source", &Resource::source)
	.def_readwrite("dump_dir", &Resource::dump_dir)
;

py::class_<::staywalk::Tex2d,Resource, std::shared_ptr<::staywalk::Tex2d>>(__module, "Tex2d")
;

py::class_<::staywalk::RObject,Object, std::shared_ptr<::staywalk::RObject>>(__module, "RObject")
	.def(py::init<const string &>())
;

py::class_<::staywalk::RTex,RObject, std::shared_ptr<::staywalk::RTex>>(__module, "RTex")
	.def_readwrite("tex", &RTex::tex)
	.def_readwrite("mipmap", &RTex::mipmap)
	.def_readwrite("wrap_s", &RTex::wrap_s)
	.def_readwrite("wrap_t", &RTex::wrap_t)
	.def_readwrite("min_filter", &RTex::min_filter)
	.def_readwrite("mag_filter", &RTex::mag_filter)
;

py::class_<::staywalk::RShader,RObject, std::shared_ptr<::staywalk::RShader>>(__module, "RShader")
	.def_readwrite("shadertype", &RShader::shadertype)
	.def_readwrite("code", &RShader::code)
;

py::class_<::staywalk::RUniform,Object, std::shared_ptr<::staywalk::RUniform>>(__module, "RUniform")
;

py::class_<::staywalk::RProgram,RObject, std::shared_ptr<::staywalk::RProgram>>(__module, "RProgram")
	.def(py::init<const string &>())
	.def_readwrite("vs", &RProgram::vs)
	.def_readwrite("fs", &RProgram::fs)
	.def_readwrite("gs", &RProgram::gs)
;

py::class_<::staywalk::Material,Object, std::shared_ptr<::staywalk::Material>>(__module, "Material")
	.def(py::init<const string &>())
	.def("add_tex", &Material::add_tex)
	.def("add_uniform", &Material::add_uniform)
	.def("is_same", &Material::is_same)
	.def_readwrite("program", &Material::program)
;

py::class_<::staywalk::Camera,GameObject, std::shared_ptr<::staywalk::Camera>>(__module, "Camera")
	.def(py::init<const string &>())
	.def("look_actor", &Camera::look_actor)
	.def_readwrite("porject_type", &Camera::porject_type)
	.def_readwrite("fov", &Camera::fov)
	.def_readwrite("aspect", &Camera::aspect)
	.def_readwrite("near", &Camera::near)
	.def_readwrite("far", &Camera::far)
;

py::class_<::staywalk::Light,GameObject, std::shared_ptr<::staywalk::Light>>(__module, "Light")
	.def(py::init<const string &>())
;

py::class_<::staywalk::Utility, std::shared_ptr<::staywalk::Utility>>(__module, "Utility")
	.def_static("create_tex", &Utility::create_tex)
;

py::class_<::staywalk::Engine, std::shared_ptr<::staywalk::Engine>>(__module, "Engine")
	.def_static("get_engine", &Engine::get_engine)
	.def_static("get_world", &Engine::get_world)
	.def_static("get_console", &Engine::get_console)
	.def("monitor_file", &Engine::monitor_file)
	.def("cancel_monitor_file", &Engine::cancel_monitor_file)
	.def("set_world", &Engine::set_world)
	.def("query_program", &Engine::query_program)
	.def("get_input_mgr", &Engine::get_input_mgr, py::return_value_policy::reference_internal)
	.def("get_view_size", &Engine::get_view_size)
	.def("set_view_size", &Engine::set_view_size)
	.def("select", &Engine::select)
	.def("get_selected", &Engine::get_selected)
;

py::class_<::staywalk::World, std::shared_ptr<::staywalk::World>>(__module, "World")
	.def_static("create_empty_world", &World::create_empty_world)
	.def_static("load_marry_world", &World::load_marry_world)
	.def_static("load", &World::load)
	.def("get_name", &World::get_name, py::return_value_policy::reference_internal)
	.def("set_name", &World::set_name)
	.def("get_actors", &World::get_actors, py::return_value_policy::reference_internal)
	.def("get_cameras", &World::get_cameras, py::return_value_policy::reference_internal)
	.def("get_lights", &World::get_lights, py::return_value_policy::reference_internal)
	.def("add_actor", &World::add_actor)
	.def("remove_actor", &World::remove_actor)
	.def("add_camera", &World::add_camera)
	.def("remove_camera", &World::remove_camera)
	.def("activate_camera", &World::activate_camera)
	.def("get_activated_camera", &World::get_activated_camera)
	.def("add_light", &World::add_light)
	.def("remove_light", &World::remove_light)
	.def("get_all_assets", &World::get_all_assets, py::return_value_policy::reference_internal)
	.def("add_asset", &World::add_asset)
	.def("remove_asset", &World::remove_asset)
;

py::class_<::staywalk::GameComponent,Object, std::shared_ptr<::staywalk::GameComponent>>(__module, "GameComponent")
	.def(py::init<const string &>())
;

py::class_<::staywalk::Mesh,RObject,Drawable, std::shared_ptr<::staywalk::Mesh>>(__module, "Mesh")
	.def(py::init<const string &>())
	.def(py::init<const vector<Vertex> &,const vector<unsigned int> &,const string &>())
	.def_static("create_simple_mesh", &Mesh::create_simple_mesh)
	.def_static("create_plane", &Mesh::create_plane)
	.def("get_aabb", &Mesh::get_aabb)
	.def("compute_aabb", &Mesh::compute_aabb)
	.def_readwrite("vertices", &Mesh::vertices)
	.def_readwrite("indices", &Mesh::indices)
;

py::class_<::staywalk::StaticMeshComponent,GameComponent,Drawable, std::shared_ptr<::staywalk::StaticMeshComponent>>(__module, "StaticMeshComponent")
	.def(py::init<const string &>())
	.def("add_mesh", &StaticMeshComponent::add_mesh)
	.def("update_material", &StaticMeshComponent::update_material)
	.def("get_aabb", &StaticMeshComponent::get_aabb)
	.def_readwrite("meshs", &StaticMeshComponent::meshs)
	.def_readwrite("transform", &StaticMeshComponent::transform)
;

py::class_<::staywalk::Terrain,Actor, std::shared_ptr<::staywalk::Terrain>>(__module, "Terrain")
	.def(py::init<const string &>())
	.def("init_with_plane", &Terrain::init_with_plane)
;


}
void ::staywalk::reflect::py_bind_auto(py::module& __module) { bind_auto(__module);}  

