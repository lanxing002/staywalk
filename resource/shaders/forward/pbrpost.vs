#version 330 core
layout (location = 0) in vec3 vs_pos;
layout (location = 1) in vec2 vs_texcoord;

out vec2 fs_texcoord;	
void main(){
    fs_texcoord = vs_texcoord;
    gl_Position = vec4(vs_pos, 1.0f); 
};
