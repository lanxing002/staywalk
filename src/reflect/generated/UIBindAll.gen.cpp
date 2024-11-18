#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src\reflect\ConstructUI.h"
#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Object.h"

void ::staywalk::Object::construct_basic_ui() const {
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(name)>()) 
        staywalk::reflect::UIHelper::construct_ui("name", name);
}



void ::staywalk::Object::construct_basic_ui() const {
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(name)>()) 
        staywalk::reflect::UIHelper::construct_ui("name", name);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\GameObject.h"

void ::staywalk::GameObject::construct_basic_ui() const {
    Object::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(transform)>()) 
        staywalk::reflect::UIHelper::construct_ui("transform", transform);
}



void ::staywalk::GameObject::construct_basic_ui() const {
    Object::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(transform)>()) 
        staywalk::reflect::UIHelper::construct_ui("transform", transform);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\GameComponent.h"

void ::staywalk::GameComponent::construct_basic_ui() const {
    Object::construct_basic_ui();
}



void ::staywalk::GameComponent::construct_basic_ui() const {
    Object::construct_obj_ui();
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::Resource::construct_basic_ui() const {
    Object::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(source)>()) 
        staywalk::reflect::UIHelper::construct_ui("source", source);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(dump_dir)>()) 
        staywalk::reflect::UIHelper::construct_ui("dump_dir", dump_dir);
}



void ::staywalk::Resource::construct_basic_ui() const {
    Object::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(source)>()) 
        staywalk::reflect::UIHelper::construct_ui("source", source);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(dump_dir)>()) 
        staywalk::reflect::UIHelper::construct_ui("dump_dir", dump_dir);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::Shader::construct_basic_ui() const {
    Resource::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(code)>()) 
        staywalk::reflect::UIHelper::construct_ui("code", code);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(shader_type)>()) 
        staywalk::reflect::UIHelper::construct_ui("shader_type", shader_type);
}



void ::staywalk::Shader::construct_basic_ui() const {
    Resource::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(code)>()) 
        staywalk::reflect::UIHelper::construct_ui("code", code);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(shader_type)>()) 
        staywalk::reflect::UIHelper::construct_ui("shader_type", shader_type);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::Tex2d::construct_basic_ui() const {
    Resource::construct_basic_ui();
}



void ::staywalk::Tex2d::construct_basic_ui() const {
    Resource::construct_obj_ui();
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RObject::construct_basic_ui() const {
    Object::construct_basic_ui();
}



void ::staywalk::RObject::construct_basic_ui() const {
    Object::construct_obj_ui();
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RTex::construct_basic_ui() const {
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



void ::staywalk::RTex::construct_basic_ui() const {
    RObject::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(tex)>()) 
        staywalk::reflect::UIHelper::construct_ui("tex", tex);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mipmap)>()) 
        staywalk::reflect::UIHelper::construct_ui("mipmap", mipmap);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_s)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_s", wrap_s);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(wrap_t)>()) 
        staywalk::reflect::UIHelper::construct_ui("wrap_t", wrap_t);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(min_filter)>()) 
        staywalk::reflect::UIHelper::construct_ui("min_filter", min_filter);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mag_filter)>()) 
        staywalk::reflect::UIHelper::construct_ui("mag_filter", mag_filter);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RShader::construct_basic_ui() const {
    RObject::construct_basic_ui();
}



void ::staywalk::RShader::construct_basic_ui() const {
    RObject::construct_obj_ui();
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RProgram::construct_basic_ui() const {
    RObject::construct_basic_ui();
}



void ::staywalk::RProgram::construct_basic_ui() const {
    RObject::construct_obj_ui();
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RenderObject.h"

void ::staywalk::RUniform::construct_basic_ui() const {
    RObject::construct_basic_ui();
}



void ::staywalk::RUniform::construct_basic_ui() const {
    RObject::construct_obj_ui();
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Material.h"

void ::staywalk::Material::construct_basic_ui() const {
    Object::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(shader_)>()) 
        staywalk::reflect::UIHelper::construct_ui("shader_", shader_);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(uniforms_)>()) 
        staywalk::reflect::UIHelper::construct_ui("uniforms_", uniforms_);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(texs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("texs_", texs_);
}



void ::staywalk::Material::construct_basic_ui() const {
    Object::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(shader_)>()) 
        staywalk::reflect::UIHelper::construct_ui("shader_", shader_);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(uniforms_)>()) 
        staywalk::reflect::UIHelper::construct_ui("uniforms_", uniforms_);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(texs_)>()) 
        staywalk::reflect::UIHelper::construct_ui("texs_", texs_);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\RMesh.h"

void ::staywalk::RMesh::construct_basic_ui() const {
    RObject::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(vertices)>()) 
        staywalk::reflect::UIHelper::construct_ui("vertices", vertices);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(indices)>()) 
        staywalk::reflect::UIHelper::construct_ui("indices", indices);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(mat)>()) 
        staywalk::reflect::UIHelper::construct_ui("mat", mat);
}



void ::staywalk::RMesh::construct_basic_ui() const {
    RObject::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(vertices)>()) 
        staywalk::reflect::UIHelper::construct_ui("vertices", vertices);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(indices)>()) 
        staywalk::reflect::UIHelper::construct_ui("indices", indices);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(mat)>()) 
        staywalk::reflect::UIHelper::construct_ui("mat", mat);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\StaticMeshComponent.h"

void ::staywalk::StaticMeshComponent::construct_basic_ui() const {
    GameComponent::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(meshs)>()) 
        staywalk::reflect::UIHelper::construct_ui("meshs", meshs);
}



void ::staywalk::StaticMeshComponent::construct_basic_ui() const {
    GameComponent::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(meshs)>()) 
        staywalk::reflect::UIHelper::construct_ui("meshs", meshs);
}



#include "C:/Users/lanxi/Documents/lanxing/codes/ErJiu/staywalk/src/engine\Actor.h"

void ::staywalk::Actor::construct_basic_ui() const {
    GameObject::construct_basic_ui();
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(sm_comp)>()) 
        staywalk::reflect::UIHelper::construct_ui("sm_comp", sm_comp);
    if constexpr (::staywalk::reflect::UIHelper::is_basic<decltype(ssm_comp)>()) 
        staywalk::reflect::UIHelper::construct_ui("ssm_comp", ssm_comp);
}



void ::staywalk::Actor::construct_basic_ui() const {
    GameObject::construct_obj_ui();
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(sm_comp)>()) 
        staywalk::reflect::UIHelper::construct_ui("sm_comp", sm_comp);
    if constexpr (!::staywalk::reflect::UIHelper::is_basic<decltype(ssm_comp)>()) 
        staywalk::reflect::UIHelper::construct_ui("ssm_comp", ssm_comp);
}



