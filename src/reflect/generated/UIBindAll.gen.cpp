#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src\reflect\ConstructUI.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\Object.h"

void ::staywalk::Object::construct_basic_ui() {
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(name)>()) 
        staywalk::reflect::UIHelper::construct_ui("name", name);
}



void ::staywalk::Object::construct_obj_ui() {
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(name)>()){ 
        //if (ImGui::TreeNode("name")){
            staywalk::reflect::UIHelper::construct_ui("name", name);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\GameObject.h"

void ::staywalk::GameObject::construct_basic_ui() {
    Object::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(transform)>()) 
        staywalk::reflect::UIHelper::construct_ui("transform", transform);
}



void ::staywalk::GameObject::construct_obj_ui() {
    Object::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(transform)>()){ 
        //if (ImGui::TreeNode("transform")){
            staywalk::reflect::UIHelper::construct_ui("transform", transform);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\GameComponent.h"

void ::staywalk::GameComponent::construct_basic_ui() {
    Object::construct_basic_ui();
}



void ::staywalk::GameComponent::construct_obj_ui() {
    Object::construct_obj_ui();
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::Resource::construct_basic_ui() {
    Object::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(source)>()) 
        staywalk::reflect::UIHelper::construct_ui("source", source);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(dump_dir)>()) 
        staywalk::reflect::UIHelper::construct_ui("dump_dir", dump_dir);
}



void ::staywalk::Resource::construct_obj_ui() {
    Object::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(source)>()){ 
        //if (ImGui::TreeNode("source")){
            staywalk::reflect::UIHelper::construct_ui("source", source);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(dump_dir)>()){ 
        //if (ImGui::TreeNode("dump_dir")){
            staywalk::reflect::UIHelper::construct_ui("dump_dir", dump_dir);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::Shader::construct_basic_ui() {
    Resource::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(code)>()) 
        staywalk::reflect::UIHelper::construct_ui("code", code);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(shader_type)>()) 
        staywalk::reflect::UIHelper::construct_ui("shader_type", shader_type);
}



void ::staywalk::Shader::construct_obj_ui() {
    Resource::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(code)>()){ 
        //if (ImGui::TreeNode("code")){
            staywalk::reflect::UIHelper::construct_ui("code", code);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(shader_type)>()){ 
        //if (ImGui::TreeNode("shader_type")){
            staywalk::reflect::UIHelper::construct_ui("shader_type", shader_type);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::Tex2d::construct_basic_ui() {
    Resource::construct_basic_ui();
}



void ::staywalk::Tex2d::construct_obj_ui() {
    Resource::construct_obj_ui();
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::RObject::construct_basic_ui() {
    Object::construct_basic_ui();
}



void ::staywalk::RObject::construct_obj_ui() {
    Object::construct_obj_ui();
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::RTex::construct_basic_ui() {
    RObject::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(tex)>()) 
        staywalk::reflect::UIHelper::construct_ui("tex", tex);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mipmap)>()) 
        staywalk::reflect::UIHelper::construct_ui("mipmap", mipmap);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_s", wrap_s);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_t", wrap_t);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(min_filter)>()) 
        staywalk::reflect::UIHelper::construct_ui("min_filter", min_filter);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter)>()) 
        staywalk::reflect::UIHelper::construct_ui("mag_filter", mag_filter);
}



void ::staywalk::RTex::construct_obj_ui() {
    RObject::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(tex)>()){ 
        //if (ImGui::TreeNode("tex")){
            staywalk::reflect::UIHelper::construct_ui("tex", tex);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mipmap)>()){ 
        //if (ImGui::TreeNode("mipmap")){
            staywalk::reflect::UIHelper::construct_ui("mipmap", mipmap);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s)>()){ 
        //if (ImGui::TreeNode("wrap_s")){
            staywalk::reflect::UIHelper::construct_ui("wrap_s", wrap_s);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t)>()){ 
        //if (ImGui::TreeNode("wrap_t")){
            staywalk::reflect::UIHelper::construct_ui("wrap_t", wrap_t);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(min_filter)>()){ 
        //if (ImGui::TreeNode("min_filter")){
            staywalk::reflect::UIHelper::construct_ui("min_filter", min_filter);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter)>()){ 
        //if (ImGui::TreeNode("mag_filter")){
            staywalk::reflect::UIHelper::construct_ui("mag_filter", mag_filter);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::RShader::construct_basic_ui() {
    RObject::construct_basic_ui();
}



void ::staywalk::RShader::construct_obj_ui() {
    RObject::construct_obj_ui();
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::RProgram::construct_basic_ui() {
    RObject::construct_basic_ui();
}



void ::staywalk::RProgram::construct_obj_ui() {
    RObject::construct_obj_ui();
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::RUniform::construct_basic_ui() {
    RObject::construct_basic_ui();
}



void ::staywalk::RUniform::construct_obj_ui() {
    RObject::construct_obj_ui();
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\Material.h"

void ::staywalk::Material::construct_basic_ui() {
    Object::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(shader_)>()) 
        staywalk::reflect::UIHelper::construct_ui("shader_", shader_);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(uniforms_)>()) 
        staywalk::reflect::UIHelper::construct_ui("uniforms_", uniforms_);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(texs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("texs_", texs_);
}



void ::staywalk::Material::construct_obj_ui() {
    Object::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(shader_)>()){ 
        //if (ImGui::TreeNode("shader_")){
            staywalk::reflect::UIHelper::construct_ui("shader_", shader_);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(uniforms_)>()){ 
        //if (ImGui::TreeNode("uniforms_")){
            staywalk::reflect::UIHelper::construct_ui("uniforms_", uniforms_);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(texs_)>()){ 
        //if (ImGui::TreeNode("texs_")){
            staywalk::reflect::UIHelper::construct_ui("texs_", texs_);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RMesh.h"

void ::staywalk::RMesh::construct_basic_ui() {
    RObject::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mat)>()) 
        staywalk::reflect::UIHelper::construct_ui("mat", mat);
}



void ::staywalk::RMesh::construct_obj_ui() {
    RObject::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mat)>()){ 
        //if (ImGui::TreeNode("mat")){
            staywalk::reflect::UIHelper::construct_ui("mat", mat);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\StaticMeshComponent.h"

void ::staywalk::StaticMeshComponent::construct_basic_ui() {
    GameComponent::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(meshs)>()) 
        staywalk::reflect::UIHelper::construct_ui("meshs", meshs);
}



void ::staywalk::StaticMeshComponent::construct_obj_ui() {
    GameComponent::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(meshs)>()){ 
        //if (ImGui::TreeNode("meshs")){
            staywalk::reflect::UIHelper::construct_ui("meshs", meshs);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\Actor.h"

void ::staywalk::Actor::construct_basic_ui() {
    GameObject::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(sm_comp)>()) 
        staywalk::reflect::UIHelper::construct_ui("sm_comp", sm_comp);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(ssm_comp)>()) 
        staywalk::reflect::UIHelper::construct_ui("ssm_comp", ssm_comp);
}



void ::staywalk::Actor::construct_obj_ui() {
    GameObject::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(sm_comp)>()){ 
        //if (ImGui::TreeNode("sm_comp")){
            staywalk::reflect::UIHelper::construct_ui("sm_comp", sm_comp);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(ssm_comp)>()){ 
        //if (ImGui::TreeNode("ssm_comp")){
            staywalk::reflect::UIHelper::construct_ui("ssm_comp", ssm_comp);
            //ImGui::TreePop();
        //}    
    }
}



