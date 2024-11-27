#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src\reflect\ConstructUI.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Object.h"

void ::staywalk::Object::construct_basic_ui(bool can_modify) {
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(name)>()) 
        staywalk::reflect::UIHelper::construct_ui("name", name, can_modify || true);
}



void ::staywalk::Object::construct_obj_ui(bool can_modify) {
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(name)>()){ 
        //if (ImGui::TreeNode("name")){
            staywalk::reflect::UIHelper::construct_ui("name", name, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\GameObject.h"

void ::staywalk::GameObject::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(transform)>()) 
        staywalk::reflect::UIHelper::construct_ui("transform", transform, can_modify || true);
}



void ::staywalk::GameObject::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(transform)>()){ 
        //if (ImGui::TreeNode("transform")){
            staywalk::reflect::UIHelper::construct_ui("transform", transform, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\GameComponent.h"

void ::staywalk::GameComponent::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
}



void ::staywalk::GameComponent::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::Resource::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(source)>()) 
        staywalk::reflect::UIHelper::construct_ui("source", source, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(dump_dir)>()) 
        staywalk::reflect::UIHelper::construct_ui("dump_dir", dump_dir, can_modify || true);
}



void ::staywalk::Resource::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(source)>()){ 
        //if (ImGui::TreeNode("source")){
            staywalk::reflect::UIHelper::construct_ui("source", source, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(dump_dir)>()){ 
        //if (ImGui::TreeNode("dump_dir")){
            staywalk::reflect::UIHelper::construct_ui("dump_dir", dump_dir, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::Tex2d::construct_basic_ui(bool can_modify) {
    Resource::construct_basic_ui(can_modify);
}



void ::staywalk::Tex2d::construct_obj_ui(bool can_modify) {
    Resource::construct_obj_ui(can_modify);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RObject::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
}



void ::staywalk::RObject::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RTex::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(tex)>()) 
        staywalk::reflect::UIHelper::construct_ui("tex", tex, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mipmap)>()) 
        staywalk::reflect::UIHelper::construct_ui("mipmap", mipmap, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_s", wrap_s, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_t", wrap_t, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(min_filter)>()) 
        staywalk::reflect::UIHelper::construct_ui("min_filter", min_filter, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter)>()) 
        staywalk::reflect::UIHelper::construct_ui("mag_filter", mag_filter, can_modify || true);
}



void ::staywalk::RTex::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(tex)>()){ 
        //if (ImGui::TreeNode("tex")){
            staywalk::reflect::UIHelper::construct_ui("tex", tex, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mipmap)>()){ 
        //if (ImGui::TreeNode("mipmap")){
            staywalk::reflect::UIHelper::construct_ui("mipmap", mipmap, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s)>()){ 
        //if (ImGui::TreeNode("wrap_s")){
            staywalk::reflect::UIHelper::construct_ui("wrap_s", wrap_s, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t)>()){ 
        //if (ImGui::TreeNode("wrap_t")){
            staywalk::reflect::UIHelper::construct_ui("wrap_t", wrap_t, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(min_filter)>()){ 
        //if (ImGui::TreeNode("min_filter")){
            staywalk::reflect::UIHelper::construct_ui("min_filter", min_filter, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter)>()){ 
        //if (ImGui::TreeNode("mag_filter")){
            staywalk::reflect::UIHelper::construct_ui("mag_filter", mag_filter, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RShader::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(shadertype)>()) 
        staywalk::reflect::UIHelper::construct_ui("shadertype", shadertype, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(code)>()) 
        staywalk::reflect::UIHelper::construct_ui("code", code, can_modify || true);
}



void ::staywalk::RShader::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(shadertype)>()){ 
        //if (ImGui::TreeNode("shadertype")){
            staywalk::reflect::UIHelper::construct_ui("shadertype", shadertype, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(code)>()){ 
        //if (ImGui::TreeNode("code")){
            staywalk::reflect::UIHelper::construct_ui("code", code, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RProgram::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(vs)>()) 
        staywalk::reflect::UIHelper::construct_ui("vs", vs, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(fs)>()) 
        staywalk::reflect::UIHelper::construct_ui("fs", fs, can_modify || true);
}



void ::staywalk::RProgram::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(vs)>()){ 
        //if (ImGui::TreeNode("vs")){
            staywalk::reflect::UIHelper::construct_ui("vs", vs, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(fs)>()){ 
        //if (ImGui::TreeNode("fs")){
            staywalk::reflect::UIHelper::construct_ui("fs", fs, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RUniform::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
}



void ::staywalk::RUniform::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Material.h"

void ::staywalk::Material::construct_basic_ui(bool can_modify) {
    Object::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(program)>()) 
        staywalk::reflect::UIHelper::construct_ui("program", program, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(uniforms_)>()) 
        staywalk::reflect::UIHelper::construct_ui("uniforms_", uniforms_, can_modify || false);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(texs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("texs_", texs_, can_modify || false);
}



void ::staywalk::Material::construct_obj_ui(bool can_modify) {
    Object::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(program)>()){ 
        //if (ImGui::TreeNode("program")){
            staywalk::reflect::UIHelper::construct_ui("program", program, can_modify || true);
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



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RMesh.h"

void ::staywalk::RMesh::construct_basic_ui(bool can_modify) {
    RObject::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mat)>()) 
        staywalk::reflect::UIHelper::construct_ui("mat", mat, can_modify || true);
}



void ::staywalk::RMesh::construct_obj_ui(bool can_modify) {
    RObject::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mat)>()){ 
        //if (ImGui::TreeNode("mat")){
            staywalk::reflect::UIHelper::construct_ui("mat", mat, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\StaticMeshComponent.h"

void ::staywalk::StaticMeshComponent::construct_basic_ui(bool can_modify) {
    GameComponent::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(meshs)>()) 
        staywalk::reflect::UIHelper::construct_ui("meshs", meshs, can_modify || true);
}



void ::staywalk::StaticMeshComponent::construct_obj_ui(bool can_modify) {
    GameComponent::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(meshs)>()){ 
        //if (ImGui::TreeNode("meshs")){
            staywalk::reflect::UIHelper::construct_ui("meshs", meshs, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Actor.h"

void ::staywalk::Actor::construct_basic_ui(bool can_modify) {
    GameObject::construct_basic_ui(can_modify);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(sm_comp)>()) 
        staywalk::reflect::UIHelper::construct_ui("sm_comp", sm_comp, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(ssm_comp)>()) 
        staywalk::reflect::UIHelper::construct_ui("ssm_comp", ssm_comp, can_modify || true);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(shader_type)>()) 
        staywalk::reflect::UIHelper::construct_ui("shader_type", shader_type, can_modify || true);
}



void ::staywalk::Actor::construct_obj_ui(bool can_modify) {
    GameObject::construct_obj_ui(can_modify);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(sm_comp)>()){ 
        //if (ImGui::TreeNode("sm_comp")){
            staywalk::reflect::UIHelper::construct_ui("sm_comp", sm_comp, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(ssm_comp)>()){ 
        //if (ImGui::TreeNode("ssm_comp")){
            staywalk::reflect::UIHelper::construct_ui("ssm_comp", ssm_comp, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(shader_type)>()){ 
        //if (ImGui::TreeNode("shader_type")){
            staywalk::reflect::UIHelper::construct_ui("shader_type", shader_type, can_modify || true);
            //ImGui::TreePop();
        //}    
    }
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Camera.h"

void ::staywalk::Camera::construct_basic_ui(bool can_modify) {
    GameObject::construct_basic_ui(can_modify);
}



void ::staywalk::Camera::construct_obj_ui(bool can_modify) {
    GameObject::construct_obj_ui(can_modify);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Light.h"

void ::staywalk::Light::construct_basic_ui(bool can_modify) {
    GameObject::construct_basic_ui(can_modify);
}



void ::staywalk::Light::construct_obj_ui(bool can_modify) {
    GameObject::construct_obj_ui(can_modify);
}



