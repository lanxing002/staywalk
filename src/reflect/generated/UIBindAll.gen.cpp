#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src\reflect\ConstructUI.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Object.h"

void ::staywalk::Object::construct_basic_ui(bool read_only) {
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(name)>()) 
        staywalk::reflect::UIHelper::construct_ui("name", name, read_only || false);
}



void ::staywalk::Object::construct_obj_ui(bool read_only) {
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(name)>()){ 
        //if (ImGui::TreeNode("name")){
            staywalk::reflect::UIHelper::construct_ui("name", name, read_only || false);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\GameObject.h"

void ::staywalk::GameObject::construct_basic_ui(bool read_only) {
    Object::construct_basic_ui(read_only);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(transform)>()) 
        staywalk::reflect::UIHelper::construct_ui("transform", transform, read_only || false);
}



void ::staywalk::GameObject::construct_obj_ui(bool read_only) {
    Object::construct_obj_ui(read_only);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(transform)>()){ 
        //if (ImGui::TreeNode("transform")){
            staywalk::reflect::UIHelper::construct_ui("transform", transform, read_only || false);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\GameComponent.h"

void ::staywalk::GameComponent::construct_basic_ui(bool read_only) {
    Object::construct_basic_ui(read_only);
}



void ::staywalk::GameComponent::construct_obj_ui(bool read_only) {
    Object::construct_obj_ui(read_only);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::Resource::construct_basic_ui(bool read_only) {
    Object::construct_basic_ui(read_only);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(source)>()) 
        staywalk::reflect::UIHelper::construct_ui("source", source, read_only || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(dump_dir)>()) 
        staywalk::reflect::UIHelper::construct_ui("dump_dir", dump_dir, read_only || false);
}



void ::staywalk::Resource::construct_obj_ui(bool read_only) {
    Object::construct_obj_ui(read_only);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(source)>()){ 
        //if (ImGui::TreeNode("source")){
            staywalk::reflect::UIHelper::construct_ui("source", source, read_only || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(dump_dir)>()){ 
        //if (ImGui::TreeNode("dump_dir")){
            staywalk::reflect::UIHelper::construct_ui("dump_dir", dump_dir, read_only || false);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::Shader::construct_basic_ui(bool read_only) {
    Resource::construct_basic_ui(read_only);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(code)>()) 
        staywalk::reflect::UIHelper::construct_ui("code", code, read_only || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(shader_type)>()) 
        staywalk::reflect::UIHelper::construct_ui("shader_type", shader_type, read_only || false);
}



void ::staywalk::Shader::construct_obj_ui(bool read_only) {
    Resource::construct_obj_ui(read_only);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(code)>()){ 
        //if (ImGui::TreeNode("code")){
            staywalk::reflect::UIHelper::construct_ui("code", code, read_only || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(shader_type)>()){ 
        //if (ImGui::TreeNode("shader_type")){
            staywalk::reflect::UIHelper::construct_ui("shader_type", shader_type, read_only || false);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::Tex2d::construct_basic_ui(bool read_only) {
    Resource::construct_basic_ui(read_only);
}



void ::staywalk::Tex2d::construct_obj_ui(bool read_only) {
    Resource::construct_obj_ui(read_only);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RObject::construct_basic_ui(bool read_only) {
    Object::construct_basic_ui(read_only);
}



void ::staywalk::RObject::construct_obj_ui(bool read_only) {
    Object::construct_obj_ui(read_only);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RTex::construct_basic_ui(bool read_only) {
    RObject::construct_basic_ui(read_only);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(tex)>()) 
        staywalk::reflect::UIHelper::construct_ui("tex", tex, read_only || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mipmap)>()) 
        staywalk::reflect::UIHelper::construct_ui("mipmap", mipmap, read_only || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_s", wrap_s, read_only || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_t", wrap_t, read_only || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(min_filter)>()) 
        staywalk::reflect::UIHelper::construct_ui("min_filter", min_filter, read_only || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter)>()) 
        staywalk::reflect::UIHelper::construct_ui("mag_filter", mag_filter, read_only || false);
}



void ::staywalk::RTex::construct_obj_ui(bool read_only) {
    RObject::construct_obj_ui(read_only);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(tex)>()){ 
        //if (ImGui::TreeNode("tex")){
            staywalk::reflect::UIHelper::construct_ui("tex", tex, read_only || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mipmap)>()){ 
        //if (ImGui::TreeNode("mipmap")){
            staywalk::reflect::UIHelper::construct_ui("mipmap", mipmap, read_only || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s)>()){ 
        //if (ImGui::TreeNode("wrap_s")){
            staywalk::reflect::UIHelper::construct_ui("wrap_s", wrap_s, read_only || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t)>()){ 
        //if (ImGui::TreeNode("wrap_t")){
            staywalk::reflect::UIHelper::construct_ui("wrap_t", wrap_t, read_only || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(min_filter)>()){ 
        //if (ImGui::TreeNode("min_filter")){
            staywalk::reflect::UIHelper::construct_ui("min_filter", min_filter, read_only || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter)>()){ 
        //if (ImGui::TreeNode("mag_filter")){
            staywalk::reflect::UIHelper::construct_ui("mag_filter", mag_filter, read_only || false);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RShader::construct_basic_ui(bool read_only) {
    RObject::construct_basic_ui(read_only);
}



void ::staywalk::RShader::construct_obj_ui(bool read_only) {
    RObject::construct_obj_ui(read_only);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RProgram::construct_basic_ui(bool read_only) {
    RObject::construct_basic_ui(read_only);
}



void ::staywalk::RProgram::construct_obj_ui(bool read_only) {
    RObject::construct_obj_ui(read_only);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RUniform::construct_basic_ui(bool read_only) {
    RObject::construct_basic_ui(read_only);
}



void ::staywalk::RUniform::construct_obj_ui(bool read_only) {
    RObject::construct_obj_ui(read_only);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Material.h"

void ::staywalk::Material::construct_basic_ui(bool read_only) {
    Object::construct_basic_ui(read_only);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(shader_)>()) 
        staywalk::reflect::UIHelper::construct_ui("shader_", shader_, read_only || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(uniforms_)>()) 
        staywalk::reflect::UIHelper::construct_ui("uniforms_", uniforms_, read_only || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(texs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("texs_", texs_, read_only || true);
}



void ::staywalk::Material::construct_obj_ui(bool read_only) {
    Object::construct_obj_ui(read_only);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(shader_)>()){ 
        //if (ImGui::TreeNode("shader_")){
            staywalk::reflect::UIHelper::construct_ui("shader_", shader_, read_only || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(uniforms_)>()){ 
        //if (ImGui::TreeNode("uniforms_")){
            staywalk::reflect::UIHelper::construct_ui("uniforms_", uniforms_, read_only || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(texs_)>()){ 
        //if (ImGui::TreeNode("texs_")){
            staywalk::reflect::UIHelper::construct_ui("texs_", texs_, read_only || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RMesh.h"

void ::staywalk::RMesh::construct_basic_ui(bool read_only) {
    RObject::construct_basic_ui(read_only);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mat)>()) 
        staywalk::reflect::UIHelper::construct_ui("mat", mat, read_only || false);
}



void ::staywalk::RMesh::construct_obj_ui(bool read_only) {
    RObject::construct_obj_ui(read_only);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mat)>()){ 
        //if (ImGui::TreeNode("mat")){
            staywalk::reflect::UIHelper::construct_ui("mat", mat, read_only || false);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\StaticMeshComponent.h"

void ::staywalk::StaticMeshComponent::construct_basic_ui(bool read_only) {
    GameComponent::construct_basic_ui(read_only);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(meshs)>()) 
        staywalk::reflect::UIHelper::construct_ui("meshs", meshs, read_only || false);
}



void ::staywalk::StaticMeshComponent::construct_obj_ui(bool read_only) {
    GameComponent::construct_obj_ui(read_only);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(meshs)>()){ 
        //if (ImGui::TreeNode("meshs")){
            staywalk::reflect::UIHelper::construct_ui("meshs", meshs, read_only || false);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Actor.h"

void ::staywalk::Actor::construct_basic_ui(bool read_only) {
    GameObject::construct_basic_ui(read_only);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(sm_comp)>()) 
        staywalk::reflect::UIHelper::construct_ui("sm_comp", sm_comp, read_only || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(ssm_comp)>()) 
        staywalk::reflect::UIHelper::construct_ui("ssm_comp", ssm_comp, read_only || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(shader_type)>()) 
        staywalk::reflect::UIHelper::construct_ui("shader_type", shader_type, read_only || false);
}



void ::staywalk::Actor::construct_obj_ui(bool read_only) {
    GameObject::construct_obj_ui(read_only);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(sm_comp)>()){ 
        //if (ImGui::TreeNode("sm_comp")){
            staywalk::reflect::UIHelper::construct_ui("sm_comp", sm_comp, read_only || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(ssm_comp)>()){ 
        //if (ImGui::TreeNode("ssm_comp")){
            staywalk::reflect::UIHelper::construct_ui("ssm_comp", ssm_comp, read_only || false);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(shader_type)>()){ 
        //if (ImGui::TreeNode("shader_type")){
            staywalk::reflect::UIHelper::construct_ui("shader_type", shader_type, read_only || false);
            //ImGui::TreePop();
        //}    
    }
}



