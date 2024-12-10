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



#include "GameObject.h"

void ::staywalk::GameObject::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(transform_)>()) 
        staywalk::reflect::UIHelper::construct_ui("transform_", transform_, can_modify || true);
}



void ::staywalk::GameObject::construct_obj_ui(bool can_modify) {
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
    GameObject::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(sm_comp_)>()) 
        staywalk::reflect::UIHelper::construct_ui("sm_comp_", sm_comp_, can_modify || true);
}



void ::staywalk::Actor::construct_obj_ui(bool can_modify) {
    GameObject::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(sm_comp_)>()){ 
        //if (ImGui::TreeNode("sm_comp_")){
            staywalk::reflect::UIHelper::construct_ui("sm_comp_", sm_comp_, can_modify || true);
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

void ::staywalk::Tex2D::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
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
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(img_name_)>()) 
        staywalk::reflect::UIHelper::construct_ui("img_name_", img_name_, can_modify || true);
}



void ::staywalk::Tex2D::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
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
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(img_name_)>()){ 
        //if (ImGui::TreeNode("img_name_")){
            staywalk::reflect::UIHelper::construct_ui("img_name_", img_name_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "RenderObject.h"

void ::staywalk::CubeMap::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(img_name_)>()) 
        staywalk::reflect::UIHelper::construct_ui("img_name_", img_name_, can_modify || true);
}



void ::staywalk::CubeMap::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(img_name_)>()){ 
        //if (ImGui::TreeNode("img_name_")){
            staywalk::reflect::UIHelper::construct_ui("img_name_", img_name_, can_modify || true);
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
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(vs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("vs_", vs_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(fs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("fs_", fs_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(gs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("gs_", gs_, can_modify || true);
}



void ::staywalk::Program::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
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
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(gs_)>()){ 
        //if (ImGui::TreeNode("gs_")){
            staywalk::reflect::UIHelper::construct_ui("gs_", gs_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "Material.h"

void ::staywalk::Material::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(program_)>()) 
        staywalk::reflect::UIHelper::construct_ui("program_", program_, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(uniforms_)>()) 
        staywalk::reflect::UIHelper::construct_ui("uniforms_", uniforms_, can_modify || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(texs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("texs_", texs_, can_modify || false);
}



void ::staywalk::Material::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(program_)>()){ 
        //if (ImGui::TreeNode("program_")){
            staywalk::reflect::UIHelper::construct_ui("program_", program_, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
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



#include "Camera.h"

void ::staywalk::Camera::construct_basic_ui(bool can_modify) {
    GameObject::construct_basic_ui(can_modify);
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
    GameObject::construct_obj_ui(can_modify);
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
    GameObject::construct_basic_ui(can_modify);
}



void ::staywalk::RLight::construct_obj_ui(bool can_modify) {
    GameObject::construct_obj_ui(can_modify);
}



#include "GameComponent.h"

void ::staywalk::GameComponent::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
}



void ::staywalk::GameComponent::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
}



#include "RMesh.h"

void ::staywalk::Mesh::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
}



void ::staywalk::Mesh::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
}



#include "StaticMeshComponent.h"

void ::staywalk::StaticMeshComponent::construct_basic_ui(bool can_modify) {
    GameComponent::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(meshs)>()) 
        staywalk::reflect::UIHelper::construct_ui("meshs", meshs, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(transform)>()) 
        staywalk::reflect::UIHelper::construct_ui("transform", transform, can_modify || true);
}



void ::staywalk::StaticMeshComponent::construct_obj_ui(bool can_modify) {
    GameComponent::construct_obj_ui(can_modify);
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



