#version 330 core

in vec2 __g_tex_coords;

uniform sampler2D __g_pos;
uniform sampler2D __g_normal;
uniform sampler2D __g_albedo;
uniform sampler2D __shadow_tex;

out vec4 frag_color;

vec4 get_albedo(){
    return texture(__g_albedo, __g_tex_coords);
}

vec3 get_pos(){
    return texture(__g_pos, __g_tex_coords).xyz;
}

vec3 get_normal(){
    return texture(__g_normal, __g_tex_coords).xyz;
}

float get_shadow(){
    return 1.0;
}

/**
input data
vec4 get_albedo();
vec3 get_pos();
vec3 get_normal();
float get_shadow();

outdata 
frag_color;


*/