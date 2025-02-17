#include "ConstructUI.h"
#include "Object.h"

void ::staywalk::Object::construct_basic_ui(bool can_modify) {
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(name_)>()) 
        staywalk::reflect::UIHelper::construct_ui("name_", name_, can_modify || true);
}



void ::staywalk::Object::construct_obj_ui(bool can_modify) {
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(name_)>()){ 
        //if (ImGui::TreeNode("name_")){
            staywalk::reflect::UIHelper::construct_ui("name_", name_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "Entity.h"

void ::staywalk::Entity::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(transform_)>()) 
        staywalk::reflect::UIHelper::construct_ui("transform_", transform_, can_modify || true);
}



void ::staywalk::Entity::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(transform_)>()){ 
        //if (ImGui::TreeNode("transform_")){
            staywalk::reflect::UIHelper::construct_ui("transform_", transform_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "Actor.h"

void ::staywalk::Actor::construct_basic_ui(bool can_modify) {
    Entity::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(sm_comp_)>()) 
        staywalk::reflect::UIHelper::construct_ui("sm_comp_", sm_comp_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(skeleton_comp_)>()) 
        staywalk::reflect::UIHelper::construct_ui("skeleton_comp_", skeleton_comp_, can_modify || true);
}



void ::staywalk::Actor::construct_obj_ui(bool can_modify) {
    Entity::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(sm_comp_)>()){ 
        //if (ImGui::TreeNode("sm_comp_")){
            staywalk::reflect::UIHelper::construct_ui("sm_comp_", sm_comp_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(skeleton_comp_)>()){ 
        //if (ImGui::TreeNode("skeleton_comp_")){
            staywalk::reflect::UIHelper::construct_ui("skeleton_comp_", skeleton_comp_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "RenderObject.h"

void ::staywalk::RObject::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
}



void ::staywalk::RObject::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
}



#include "RenderObject.h"

void ::staywalk::Tex::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(img_name_)>()) 
        staywalk::reflect::UIHelper::construct_ui("img_name_", img_name_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(internal_format_)>()) 
        staywalk::reflect::UIHelper::construct_ui("internal_format_", internal_format_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(format_)>()) 
        staywalk::reflect::UIHelper::construct_ui("format_", format_, can_modify || true);
}



void ::staywalk::Tex::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(img_name_)>()){ 
        //if (ImGui::TreeNode("img_name_")){
            staywalk::reflect::UIHelper::construct_ui("img_name_", img_name_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(internal_format_)>()){ 
        //if (ImGui::TreeNode("internal_format_")){
            staywalk::reflect::UIHelper::construct_ui("internal_format_", internal_format_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(format_)>()){ 
        //if (ImGui::TreeNode("format_")){
            staywalk::reflect::UIHelper::construct_ui("format_", format_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "RenderObject.h"

void ::staywalk::Tex2D::construct_basic_ui(bool can_modify) {
    Tex::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mipmap_)>()) 
        staywalk::reflect::UIHelper::construct_ui("mipmap_", mipmap_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s_)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_s_", wrap_s_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t_)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_t_", wrap_t_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(min_filter_)>()) 
        staywalk::reflect::UIHelper::construct_ui("min_filter_", min_filter_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter_)>()) 
        staywalk::reflect::UIHelper::construct_ui("mag_filter_", mag_filter_, can_modify || true);
}



void ::staywalk::Tex2D::construct_obj_ui(bool can_modify) {
    Tex::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mipmap_)>()){ 
        //if (ImGui::TreeNode("mipmap_")){
            staywalk::reflect::UIHelper::construct_ui("mipmap_", mipmap_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s_)>()){ 
        //if (ImGui::TreeNode("wrap_s_")){
            staywalk::reflect::UIHelper::construct_ui("wrap_s_", wrap_s_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t_)>()){ 
        //if (ImGui::TreeNode("wrap_t_")){
            staywalk::reflect::UIHelper::construct_ui("wrap_t_", wrap_t_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(min_filter_)>()){ 
        //if (ImGui::TreeNode("min_filter_")){
            staywalk::reflect::UIHelper::construct_ui("min_filter_", min_filter_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter_)>()){ 
        //if (ImGui::TreeNode("mag_filter_")){
            staywalk::reflect::UIHelper::construct_ui("mag_filter_", mag_filter_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "RenderObject.h"

void ::staywalk::FrameBuffer::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
}



void ::staywalk::FrameBuffer::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
}



#include "RenderObject.h"

void ::staywalk::CubeMap::construct_basic_ui(bool can_modify) {
    Tex::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(img_name_)>()) 
        staywalk::reflect::UIHelper::construct_ui("img_name_", img_name_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(img_extension_)>()) 
        staywalk::reflect::UIHelper::construct_ui("img_extension_", img_extension_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s_)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_s_", wrap_s_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t_)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_t_", wrap_t_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_r_)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_r_", wrap_r_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(min_filter_)>()) 
        staywalk::reflect::UIHelper::construct_ui("min_filter_", min_filter_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter_)>()) 
        staywalk::reflect::UIHelper::construct_ui("mag_filter_", mag_filter_, can_modify || true);
}



void ::staywalk::CubeMap::construct_obj_ui(bool can_modify) {
    Tex::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(img_name_)>()){ 
        //if (ImGui::TreeNode("img_name_")){
            staywalk::reflect::UIHelper::construct_ui("img_name_", img_name_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(img_extension_)>()){ 
        //if (ImGui::TreeNode("img_extension_")){
            staywalk::reflect::UIHelper::construct_ui("img_extension_", img_extension_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s_)>()){ 
        //if (ImGui::TreeNode("wrap_s_")){
            staywalk::reflect::UIHelper::construct_ui("wrap_s_", wrap_s_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t_)>()){ 
        //if (ImGui::TreeNode("wrap_t_")){
            staywalk::reflect::UIHelper::construct_ui("wrap_t_", wrap_t_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_r_)>()){ 
        //if (ImGui::TreeNode("wrap_r_")){
            staywalk::reflect::UIHelper::construct_ui("wrap_r_", wrap_r_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(min_filter_)>()){ 
        //if (ImGui::TreeNode("min_filter_")){
            staywalk::reflect::UIHelper::construct_ui("min_filter_", min_filter_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter_)>()){ 
        //if (ImGui::TreeNode("mag_filter_")){
            staywalk::reflect::UIHelper::construct_ui("mag_filter_", mag_filter_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "RenderObject.h"

void ::staywalk::RenderTarget2D::construct_basic_ui(bool can_modify) {
    Tex::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s_)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_s_", wrap_s_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t_)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_t_", wrap_t_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(min_filter_)>()) 
        staywalk::reflect::UIHelper::construct_ui("min_filter_", min_filter_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter_)>()) 
        staywalk::reflect::UIHelper::construct_ui("mag_filter_", mag_filter_, can_modify || true);
}



void ::staywalk::RenderTarget2D::construct_obj_ui(bool can_modify) {
    Tex::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s_)>()){ 
        //if (ImGui::TreeNode("wrap_s_")){
            staywalk::reflect::UIHelper::construct_ui("wrap_s_", wrap_s_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t_)>()){ 
        //if (ImGui::TreeNode("wrap_t_")){
            staywalk::reflect::UIHelper::construct_ui("wrap_t_", wrap_t_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(min_filter_)>()){ 
        //if (ImGui::TreeNode("min_filter_")){
            staywalk::reflect::UIHelper::construct_ui("min_filter_", min_filter_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter_)>()){ 
        //if (ImGui::TreeNode("mag_filter_")){
            staywalk::reflect::UIHelper::construct_ui("mag_filter_", mag_filter_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "RProgram.h"

void ::staywalk::Shader::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(shadertype_)>()) 
        staywalk::reflect::UIHelper::construct_ui("shadertype_", shadertype_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(code_)>()) 
        staywalk::reflect::UIHelper::construct_ui("code_", code_, can_modify || true);
}



void ::staywalk::Shader::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(shadertype_)>()){ 
        //if (ImGui::TreeNode("shadertype_")){
            staywalk::reflect::UIHelper::construct_ui("shadertype_", shadertype_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(code_)>()){ 
        //if (ImGui::TreeNode("code_")){
            staywalk::reflect::UIHelper::construct_ui("code_", code_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "RProgram.h"

void ::staywalk::Uniform::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
}



void ::staywalk::Uniform::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
}



#include "RProgram.h"

void ::staywalk::Program::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
}



void ::staywalk::Program::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
}



#include "RProgram.h"

void ::staywalk::StdProgram::construct_basic_ui(bool can_modify) {
    Program::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(deferred_)>()) 
        staywalk::reflect::UIHelper::construct_ui("deferred_", deferred_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(vs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("vs_", vs_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(fs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("fs_", fs_, can_modify || true);
}



void ::staywalk::StdProgram::construct_obj_ui(bool can_modify) {
    Program::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(deferred_)>()){ 
        //if (ImGui::TreeNode("deferred_")){
            staywalk::reflect::UIHelper::construct_ui("deferred_", deferred_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(vs_)>()){ 
        //if (ImGui::TreeNode("vs_")){
            staywalk::reflect::UIHelper::construct_ui("vs_", vs_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(fs_)>()){ 
        //if (ImGui::TreeNode("fs_")){
            staywalk::reflect::UIHelper::construct_ui("fs_", fs_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "RProgram.h"

void ::staywalk::CSProgram::construct_basic_ui(bool can_modify) {
    Program::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(cs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("cs_", cs_, can_modify || true);
}



void ::staywalk::CSProgram::construct_obj_ui(bool can_modify) {
    Program::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(cs_)>()){ 
        //if (ImGui::TreeNode("cs_")){
            staywalk::reflect::UIHelper::construct_ui("cs_", cs_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "StateSet.h"

void ::staywalk::StateSet::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(uniforms_)>()) 
        staywalk::reflect::UIHelper::construct_ui("uniforms_", uniforms_, can_modify || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(texs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("texs_", texs_, can_modify || false);
}



void ::staywalk::StateSet::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(uniforms_)>()){ 
        //if (ImGui::TreeNode("uniforms_")){
            staywalk::reflect::UIHelper::construct_ui("uniforms_", uniforms_, can_modify || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(texs_)>()){ 
        //if (ImGui::TreeNode("texs_")){
            staywalk::reflect::UIHelper::construct_ui("texs_", texs_, can_modify || false);
            //ImGui::TreePop();
        //}    
    }
}



#include "Material.h"

void ::staywalk::Material::construct_basic_ui(bool can_modify) {
    StateSet::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(program_)>()) 
        staywalk::reflect::UIHelper::construct_ui("program_", program_, can_modify || true);
}



void ::staywalk::Material::construct_obj_ui(bool can_modify) {
    StateSet::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(program_)>()){ 
        //if (ImGui::TreeNode("program_")){
            staywalk::reflect::UIHelper::construct_ui("program_", program_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "Camera.h"

void ::staywalk::Camera::construct_basic_ui(bool can_modify) {
    Entity::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(porject_type_)>()) 
        staywalk::reflect::UIHelper::construct_ui("porject_type_", porject_type_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(fov_)>()) 
        staywalk::reflect::UIHelper::construct_ui("fov_", fov_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(aspect_)>()) 
        staywalk::reflect::UIHelper::construct_ui("aspect_", aspect_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(near_)>()) 
        staywalk::reflect::UIHelper::construct_ui("near_", near_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(far_)>()) 
        staywalk::reflect::UIHelper::construct_ui("far_", far_, can_modify || true);
}



void ::staywalk::Camera::construct_obj_ui(bool can_modify) {
    Entity::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(porject_type_)>()){ 
        //if (ImGui::TreeNode("porject_type_")){
            staywalk::reflect::UIHelper::construct_ui("porject_type_", porject_type_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(fov_)>()){ 
        //if (ImGui::TreeNode("fov_")){
            staywalk::reflect::UIHelper::construct_ui("fov_", fov_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(aspect_)>()){ 
        //if (ImGui::TreeNode("aspect_")){
            staywalk::reflect::UIHelper::construct_ui("aspect_", aspect_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(near_)>()){ 
        //if (ImGui::TreeNode("near_")){
            staywalk::reflect::UIHelper::construct_ui("near_", near_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(far_)>()){ 
        //if (ImGui::TreeNode("far_")){
            staywalk::reflect::UIHelper::construct_ui("far_", far_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "Light.h"

void ::staywalk::RLight::construct_basic_ui(bool can_modify) {
    Entity::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(light_type_)>()) 
        staywalk::reflect::UIHelper::construct_ui("light_type_", light_type_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(pos)>()) 
        staywalk::reflect::UIHelper::construct_ui("pos", pos, can_modify || true);
}



void ::staywalk::RLight::construct_obj_ui(bool can_modify) {
    Entity::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(light_type_)>()){ 
        //if (ImGui::TreeNode("light_type_")){
            staywalk::reflect::UIHelper::construct_ui("light_type_", light_type_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(pos)>()){ 
        //if (ImGui::TreeNode("pos")){
            staywalk::reflect::UIHelper::construct_ui("pos", pos, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "Component.h"

void ::staywalk::Component::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
}



void ::staywalk::Component::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
}



#include "RMesh.h"

void ::staywalk::Mesh::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
}



void ::staywalk::Mesh::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
}



#include "RMesh.h"

void ::staywalk::SkeletonMesh::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
}



void ::staywalk::SkeletonMesh::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
}



#include "StaticMeshComponent.h"

void ::staywalk::StaticMeshComponent::construct_basic_ui(bool can_modify) {
    Component::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(meshs)>()) 
        staywalk::reflect::UIHelper::construct_ui("meshs", meshs, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(transform)>()) 
        staywalk::reflect::UIHelper::construct_ui("transform", transform, can_modify || true);
}



void ::staywalk::StaticMeshComponent::construct_obj_ui(bool can_modify) {
    Component::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(meshs)>()){ 
        //if (ImGui::TreeNode("meshs")){
            staywalk::reflect::UIHelper::construct_ui("meshs", meshs, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(transform)>()){ 
        //if (ImGui::TreeNode("transform")){
            staywalk::reflect::UIHelper::construct_ui("transform", transform, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "Terrain.h"

void ::staywalk::Terrain::construct_basic_ui(bool can_modify) {
    Actor::construct_basic_ui(can_modify);
}



void ::staywalk::Terrain::construct_obj_ui(bool can_modify) {
    Actor::construct_obj_ui(can_modify);
}



#include "Animation.h"

void ::staywalk::BoneTreeNode::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
}



void ::staywalk::BoneTreeNode::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
}



#include "Animation.h"

void ::staywalk::Animation::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(curr_time_)>()) 
        staywalk::reflect::UIHelper::construct_ui("curr_time_", curr_time_, can_modify || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(duration_)>()) 
        staywalk::reflect::UIHelper::construct_ui("duration_", duration_, can_modify || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(ticks_pers_)>()) 
        staywalk::reflect::UIHelper::construct_ui("ticks_pers_", ticks_pers_, can_modify || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(node_root_)>()) 
        staywalk::reflect::UIHelper::construct_ui("node_root_", node_root_, can_modify || false);
}



void ::staywalk::Animation::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(curr_time_)>()){ 
        //if (ImGui::TreeNode("curr_time_")){
            staywalk::reflect::UIHelper::construct_ui("curr_time_", curr_time_, can_modify || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(duration_)>()){ 
        //if (ImGui::TreeNode("duration_")){
            staywalk::reflect::UIHelper::construct_ui("duration_", duration_, can_modify || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(ticks_pers_)>()){ 
        //if (ImGui::TreeNode("ticks_pers_")){
            staywalk::reflect::UIHelper::construct_ui("ticks_pers_", ticks_pers_, can_modify || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(node_root_)>()){ 
        //if (ImGui::TreeNode("node_root_")){
            staywalk::reflect::UIHelper::construct_ui("node_root_", node_root_, can_modify || false);
            //ImGui::TreePop();
        //}    
    }
}



#include "SkeletonMeshComponent.h"

void ::staywalk::SkeletonMeshComponent::construct_basic_ui(bool can_modify) {
    Component::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(transform_)>()) 
        staywalk::reflect::UIHelper::construct_ui("transform_", transform_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(meshs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("meshs_", meshs_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(animation_)>()) 
        staywalk::reflect::UIHelper::construct_ui("animation_", animation_, can_modify || true);
}



void ::staywalk::SkeletonMeshComponent::construct_obj_ui(bool can_modify) {
    Component::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(transform_)>()){ 
        //if (ImGui::TreeNode("transform_")){
            staywalk::reflect::UIHelper::construct_ui("transform_", transform_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(meshs_)>()){ 
        //if (ImGui::TreeNode("meshs_")){
            staywalk::reflect::UIHelper::construct_ui("meshs_", meshs_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(animation_)>()){ 
        //if (ImGui::TreeNode("animation_")){
            staywalk::reflect::UIHelper::construct_ui("animation_", animation_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "RenderTarget.h"

void ::staywalk::RenderTarget::construct_basic_ui(bool can_modify) {
    Entity::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(camera_)>()) 
        staywalk::reflect::UIHelper::construct_ui("camera_", camera_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(post_stage_)>()) 
        staywalk::reflect::UIHelper::construct_ui("post_stage_", post_stage_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(width_)>()) 
        staywalk::reflect::UIHelper::construct_ui("width_", width_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(height_)>()) 
        staywalk::reflect::UIHelper::construct_ui("height_", height_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(program_)>()) 
        staywalk::reflect::UIHelper::construct_ui("program_", program_, can_modify || true);
}



void ::staywalk::RenderTarget::construct_obj_ui(bool can_modify) {
    Entity::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(camera_)>()){ 
        //if (ImGui::TreeNode("camera_")){
            staywalk::reflect::UIHelper::construct_ui("camera_", camera_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(post_stage_)>()){ 
        //if (ImGui::TreeNode("post_stage_")){
            staywalk::reflect::UIHelper::construct_ui("post_stage_", post_stage_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(width_)>()){ 
        //if (ImGui::TreeNode("width_")){
            staywalk::reflect::UIHelper::construct_ui("width_", width_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(height_)>()){ 
        //if (ImGui::TreeNode("height_")){
            staywalk::reflect::UIHelper::construct_ui("height_", height_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(program_)>()){ 
        //if (ImGui::TreeNode("program_")){
            staywalk::reflect::UIHelper::construct_ui("program_", program_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "DepthRenderTarget.h"

void ::staywalk::DepthRenderTarget::construct_basic_ui(bool can_modify) {
    RenderTarget::construct_basic_ui(can_modify);
}



void ::staywalk::DepthRenderTarget::construct_obj_ui(bool can_modify) {
    RenderTarget::construct_obj_ui(can_modify);
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/staywalk/src/project/SkyBox.h"

void ::staywalk::Skybox::construct_basic_ui(bool can_modify) {
    Actor::construct_basic_ui(can_modify);
}



void ::staywalk::Skybox::construct_obj_ui(bool can_modify) {
    Actor::construct_obj_ui(can_modify);
}



