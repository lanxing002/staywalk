#include "Script.h"
namespace py = pybind11;
using namespace staywalk;
#include "Object.h"
#include "GameObject.h"
#include "Actor.h"
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
#include "RMesh.h"
#include "StaticMeshComponent.h"
#include "Terrain.h"
#include "Animation.h"
#include "Animation.h"
#include "SkeletonMeshComponent.h"


static void bind_auto(py::module& __module){
py::class_<::staywalk::Object, std::shared_ptr<::staywalk::Object>>(__module, "Object")
	.def(py::init<const string &>())
	.def("get_guid", &Object::get_guid)
	.def_readwrite("name_", &Object::name_)
;

py::class_<::staywalk::GameObject,Object, std::shared_ptr<::staywalk::GameObject>>(__module, "GameObject")
	.def(py::init<const string &>())
	.def_readwrite("transform_", &GameObject::transform_)
;

py::class_<::staywalk::Actor,GameObject, std::shared_ptr<::staywalk::Actor>>(__module, "Actor")
	.def(py::init<const string &>())
	.def("get_aabb", &Actor::get_aabb)
	.def_readwrite("sm_comp_", &Actor::sm_comp_)
;

py::class_<::staywalk::RObject,Object, std::shared_ptr<::staywalk::RObject>>(__module, "RObject")
	.def(py::init<const string &>())
;

py::class_<::staywalk::Tex2D,RObject, std::shared_ptr<::staywalk::Tex2D>>(__module, "Tex2D")
	.def_readwrite("mipmap_", &Tex2D::mipmap_)
	.def_readwrite("wrap_s_", &Tex2D::wrap_s_)
	.def_readwrite("wrap_t_", &Tex2D::wrap_t_)
	.def_readwrite("min_filter_", &Tex2D::min_filter_)
	.def_readwrite("mag_filter_", &Tex2D::mag_filter_)
	.def_readwrite("img_name_", &Tex2D::img_name_)
;

py::class_<::staywalk::CubeMap,RObject, std::shared_ptr<::staywalk::CubeMap>>(__module, "CubeMap")
	.def(py::init<const string &>())
	.def_readwrite("img_name_", &CubeMap::img_name_)
	.def_readwrite("img_extension_", &CubeMap::img_extension_)
	.def_readwrite("wrap_s_", &CubeMap::wrap_s_)
	.def_readwrite("wrap_t_", &CubeMap::wrap_t_)
	.def_readwrite("wrap_r_", &CubeMap::wrap_r_)
	.def_readwrite("min_filter_", &CubeMap::min_filter_)
	.def_readwrite("mag_filter_", &CubeMap::mag_filter_)
;

py::class_<::staywalk::Shader,RObject, std::shared_ptr<::staywalk::Shader>>(__module, "Shader")
	.def_readwrite("shadertype_", &Shader::shadertype_)
	.def_readwrite("code_", &Shader::code_)
;

py::class_<::staywalk::Uniform,Object, std::shared_ptr<::staywalk::Uniform>>(__module, "Uniform")
;

py::class_<::staywalk::Program,RObject, std::shared_ptr<::staywalk::Program>>(__module, "Program")
	.def(py::init<const string &>())
	.def_readwrite("vs_", &Program::vs_)
	.def_readwrite("fs_", &Program::fs_)
	.def_readwrite("gs_", &Program::gs_)
;

py::class_<::staywalk::Material,Object, std::shared_ptr<::staywalk::Material>>(__module, "Material")
	.def(py::init<const string &>())
	.def("add_tex", &Material::add_tex)
	.def("add_uniform", &Material::add_uniform)
	.def("is_same", &Material::is_same)
	.def_readwrite("program_", &Material::program_)
;

py::class_<::staywalk::Camera,GameObject, std::shared_ptr<::staywalk::Camera>>(__module, "Camera")
	.def(py::init<const string &>())
	.def("look_actor", &Camera::look_actor)
	.def_readwrite("porject_type_", &Camera::porject_type_)
	.def_readwrite("fov_", &Camera::fov_)
	.def_readwrite("aspect_", &Camera::aspect_)
	.def_readwrite("near_", &Camera::near_)
	.def_readwrite("far_", &Camera::far_)
;

py::class_<::staywalk::RLight,GameObject, std::shared_ptr<::staywalk::RLight>>(__module, "RLight")
	.def(py::init<const string &>())
;

py::class_<::staywalk::Utility, std::shared_ptr<::staywalk::Utility>>(__module, "Utility")
	.def_static("create_tex", &Utility::create_tex)
	.def_static("create_sm_from_obj", &Utility::create_sm_from_obj)
	.def_static("create_skeleton_from_obj", &Utility::create_skeleton_from_obj)
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
	.def_readwrite("vertices_", &Mesh::vertices_)
	.def_readwrite("indices_", &Mesh::indices_)
;

py::class_<::staywalk::SkeletonMesh,RObject,Drawable, std::shared_ptr<::staywalk::SkeletonMesh>>(__module, "SkeletonMesh")
	.def(py::init<const string &>())
	.def(py::init<const vector<SkinVertex> &,const vector<unsigned int> &,const string &>())
	.def_readwrite("vertices_", &SkeletonMesh::vertices_)
	.def_readwrite("indices_", &SkeletonMesh::indices_)
	.def_readwrite("bone_mat_", &SkeletonMesh::bone_mat_)
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

py::class_<::staywalk::BoneTreeNode,Object, std::shared_ptr<::staywalk::BoneTreeNode>>(__module, "BoneTreeNode")
	.def_readwrite("transform_", &BoneTreeNode::transform_)
	.def_readwrite("children_", &BoneTreeNode::children_)
	.def_readwrite("bone_id_", &BoneTreeNode::bone_id_)
;

py::class_<::staywalk::Animation,RObject, std::shared_ptr<::staywalk::Animation>>(__module, "Animation")
	.def(py::init<const string &>())
;

py::class_<::staywalk::SkeletonMeshComponent,GameComponent,Drawable, std::shared_ptr<::staywalk::SkeletonMeshComponent>>(__module, "SkeletonMeshComponent")
	.def(py::init<const string &>())
	.def("update_material", &SkeletonMeshComponent::update_material)
	.def_readwrite("transform_", &SkeletonMeshComponent::transform_)
	.def_readwrite("meshs_", &SkeletonMeshComponent::meshs_)
	.def_readwrite("animation_", &SkeletonMeshComponent::animation_)
;


}
void ::staywalk::reflect::py_bind_auto(py::module& __module) { bind_auto(__module);}  

