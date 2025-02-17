#include "Script.h"
namespace py = pybind11;
using namespace staywalk;
#include "Object.h"
#include "Entity.h"
#include "Actor.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RProgram.h"
#include "RProgram.h"
#include "RProgram.h"
#include "RProgram.h"
#include "RProgram.h"
#include "StateSet.h"
#include "Material.h"
#include "Camera.h"
#include "Light.h"
#include "Utility.h"
#include "Engine.h"
#include "World.h"
#include "Component.h"
#include "RMesh.h"
#include "RMesh.h"
#include "StaticMeshComponent.h"
#include "Terrain.h"
#include "Animation.h"
#include "Animation.h"
#include "SkeletonMeshComponent.h"
#include "RenderTarget.h"
#include "DepthRenderTarget.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/staywalk/src/project/SkyBox.h"


static void bind_auto(py::module& __module){
py::class_<::staywalk::Object, std::shared_ptr<::staywalk::Object>>(__module, "Object")
	.def(py::init<const string &>())
	.def("get_guid", &Object::get_guid)
	.def_readwrite("name_", &Object::name_)
;

py::class_<::staywalk::Entity,Object, std::shared_ptr<::staywalk::Entity>>(__module, "Entity")
	.def(py::init<const string &>())
	.def_readwrite("transform_", &Entity::transform_)
;

py::class_<::staywalk::Actor,Entity, std::shared_ptr<::staywalk::Actor>>(__module, "Actor")
	.def(py::init<const string &>())
	.def("get_aabb", &Actor::get_aabb)
	.def_readwrite("sm_comp_", &Actor::sm_comp_)
	.def_readwrite("skeleton_comp_", &Actor::skeleton_comp_)
;

py::class_<::staywalk::RObject,Object, std::shared_ptr<::staywalk::RObject>>(__module, "RObject")
	.def(py::init<const string &>())
;

py::class_<::staywalk::Tex,RObject, std::shared_ptr<::staywalk::Tex>>(__module, "Tex")
	.def_readwrite("img_name_", &Tex::img_name_)
	.def_readwrite("internal_format_", &Tex::internal_format_)
	.def_readwrite("format_", &Tex::format_)
;

py::class_<::staywalk::Tex2D,Tex, std::shared_ptr<::staywalk::Tex2D>>(__module, "Tex2D")
	.def(py::init<const string &>())
	.def("resize", &Tex2D::resize)
	.def_readwrite("mipmap_", &Tex2D::mipmap_)
	.def_readwrite("wrap_s_", &Tex2D::wrap_s_)
	.def_readwrite("wrap_t_", &Tex2D::wrap_t_)
	.def_readwrite("min_filter_", &Tex2D::min_filter_)
	.def_readwrite("mag_filter_", &Tex2D::mag_filter_)
;

py::class_<::staywalk::FrameBuffer,RObject, std::shared_ptr<::staywalk::FrameBuffer>>(__module, "FrameBuffer")
;

py::class_<::staywalk::CubeMap,Tex, std::shared_ptr<::staywalk::CubeMap>>(__module, "CubeMap")
	.def(py::init<const string &>())
	.def_readwrite("img_name_", &CubeMap::img_name_)
	.def_readwrite("img_extension_", &CubeMap::img_extension_)
	.def_readwrite("wrap_s_", &CubeMap::wrap_s_)
	.def_readwrite("wrap_t_", &CubeMap::wrap_t_)
	.def_readwrite("wrap_r_", &CubeMap::wrap_r_)
	.def_readwrite("min_filter_", &CubeMap::min_filter_)
	.def_readwrite("mag_filter_", &CubeMap::mag_filter_)
;

py::class_<::staywalk::RenderTarget2D,Tex, std::shared_ptr<::staywalk::RenderTarget2D>>(__module, "RenderTarget2D")
	.def(py::init<const string &>())
	.def("resize", &RenderTarget2D::resize)
	.def("set_comp_flag", &RenderTarget2D::set_comp_flag)
	.def_readwrite("wrap_s_", &RenderTarget2D::wrap_s_)
	.def_readwrite("wrap_t_", &RenderTarget2D::wrap_t_)
	.def_readwrite("min_filter_", &RenderTarget2D::min_filter_)
	.def_readwrite("mag_filter_", &RenderTarget2D::mag_filter_)
;

py::class_<::staywalk::Shader,RObject, std::shared_ptr<::staywalk::Shader>>(__module, "Shader")
	.def_readwrite("shadertype_", &Shader::shadertype_)
	.def_readwrite("code_", &Shader::code_)
;

py::class_<::staywalk::Uniform,Object, std::shared_ptr<::staywalk::Uniform>>(__module, "Uniform")
;

py::class_<::staywalk::Program,RObject, std::shared_ptr<::staywalk::Program>>(__module, "Program")
;

py::class_<::staywalk::StdProgram,Program, std::shared_ptr<::staywalk::StdProgram>>(__module, "StdProgram")
	.def(py::init<const string &>())
	.def_readwrite("deferred_", &StdProgram::deferred_)
	.def_readwrite("vs_", &StdProgram::vs_)
	.def_readwrite("fs_", &StdProgram::fs_)
;

py::class_<::staywalk::CSProgram,Program, std::shared_ptr<::staywalk::CSProgram>>(__module, "CSProgram")
	.def(py::init<const string &>())
	.def("set_work_group_size", &CSProgram::set_work_group_size)
	.def_readwrite("cs_", &CSProgram::cs_)
;

py::class_<::staywalk::StateSet,Object, std::shared_ptr<::staywalk::StateSet>>(__module, "StateSet")
	.def(py::init<const string &>())
	.def("add_tex", &StateSet::add_tex)
	.def("add_uniform", &StateSet::add_uniform)
	.def("remove_tex", &StateSet::remove_tex)
	.def("remove_uniform", &StateSet::remove_uniform)
	.def("is_same", &StateSet::is_same)
	.def("get_tex_slot", &StateSet::get_tex_slot)
;

py::class_<::staywalk::Material,StateSet, std::shared_ptr<::staywalk::Material>>(__module, "Material")
	.def(py::init<const string &>())
	.def_readwrite("program_", &Material::program_)
;

py::class_<::staywalk::Camera,Entity, std::shared_ptr<::staywalk::Camera>>(__module, "Camera")
	.def(py::init<const string &>())
	.def("look_actor", &Camera::look_actor)
	.def("update_matrix", &Camera::update_matrix)
	.def_readwrite("porject_type_", &Camera::porject_type_)
	.def_readwrite("fov_", &Camera::fov_)
	.def_readwrite("aspect_", &Camera::aspect_)
	.def_readwrite("near_", &Camera::near_)
	.def_readwrite("far_", &Camera::far_)
;

py::class_<::staywalk::RLight,Entity, std::shared_ptr<::staywalk::RLight>>(__module, "RLight")
	.def(py::init<const string &>())
	.def_readwrite("light_type_", &RLight::light_type_)
	.def_readwrite("pos", &RLight::pos)
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
	.def("add_rendertarget", &World::add_rendertarget)
	.def("remove_rendertarget", &World::remove_rendertarget)
	.def("get_all_rendertargets", &World::get_all_rendertargets)
	.def("add_camera", &World::add_camera)
	.def("remove_camera", &World::remove_camera)
	.def("activate_camera", &World::activate_camera)
	.def("get_activated_camera", &World::get_activated_camera)
	.def("add_light", &World::add_light)
	.def("remove_light", &World::remove_light)
	.def("get_main_light", &World::get_main_light)
	.def("get_all_assets", &World::get_all_assets, py::return_value_policy::reference_internal)
	.def("add_asset", &World::add_asset)
	.def("remove_asset", &World::remove_asset)
;

py::class_<::staywalk::Component,Object, std::shared_ptr<::staywalk::Component>>(__module, "Component")
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
;

py::class_<::staywalk::StaticMeshComponent,Component,Drawable, std::shared_ptr<::staywalk::StaticMeshComponent>>(__module, "StaticMeshComponent")
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

py::class_<::staywalk::SkeletonMeshComponent,Component,Drawable, std::shared_ptr<::staywalk::SkeletonMeshComponent>>(__module, "SkeletonMeshComponent")
	.def(py::init<const string &>())
	.def("update_material", &SkeletonMeshComponent::update_material)
	.def_readwrite("transform_", &SkeletonMeshComponent::transform_)
	.def_readwrite("meshs_", &SkeletonMeshComponent::meshs_)
	.def_readwrite("animation_", &SkeletonMeshComponent::animation_)
;

py::class_<::staywalk::RenderTarget,Entity, std::shared_ptr<::staywalk::RenderTarget>>(__module, "RenderTarget")
	.def(py::init<const string &>())
	.def_readwrite("camera_", &RenderTarget::camera_)
	.def_readwrite("post_stage_", &RenderTarget::post_stage_)
	.def_readwrite("width_", &RenderTarget::width_)
	.def_readwrite("height_", &RenderTarget::height_)
	.def_readwrite("program_", &RenderTarget::program_)
;

py::class_<::staywalk::DepthRenderTarget,RenderTarget, std::shared_ptr<::staywalk::DepthRenderTarget>>(__module, "DepthRenderTarget")
	.def(py::init<const string &>())
;

py::class_<::staywalk::Skybox,Actor, std::shared_ptr<::staywalk::Skybox>>(__module, "Skybox")
	.def(py::init<const string &>())
	.def_static("create", &Skybox::create)
;


}
void ::staywalk::reflect::py_bind_auto(py::module& __module) { bind_auto(__module);}  

