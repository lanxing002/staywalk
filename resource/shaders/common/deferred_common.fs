#version 330 core

layout (location = 0) out vec3 nod_g_pos;
layout (location = 1) out vec3 nod_g_normal;
layout (location = 2) out vec4 nod_g_albedo;

// input data layout
in vec3 nod_in_world_pos;
in vec3 nod_in_norm;
in vec2 in_texcoord;
in vec3 in_tangent;
in vec3 in_bitangent;
in vec3 nod_in_light_view_pos;

vec3 in_norm;

vec4 get_albedo();

vec3 get_normal();

void main(){
    in_norm = normalize(nod_in_norm);

    nod_g_pos = nod_in_world_pos;
    nod_g_normal = get_normal();
    nod_g_albedo = get_albedo();
}

/**
in vec3 in_norm;
in vec2 in_texcoord;
in vec3 in_tangent;
in vec3 in_bitangent;

vec3 get_albedo();
vec3 get_...();
*/

// ===================user code=======================
