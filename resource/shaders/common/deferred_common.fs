#version 330 core

layout (location = 0) out vec3 g_pos;
layout (location = 1) out vec3 g_normal;
layout (location = 2) out vec4 g_albedo;

// input data layout
in vec3 fs_world_pos;
in vec3 fs_norm;
in vec2 fs_texcoord;
in vec3 fs_tangent;
in vec3 fs_bitangent;
in vec3 fs_light_view_pos;


vec4 get_albedo();

vec3 get_normal();

void main(){
    g_pos = fs_world_pos;
    g_normal = get_normal();
    g_albedo = get_albedo();
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
