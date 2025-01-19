
#version 330 core
in vec2 fs_texcoord;	
out vec4 FragColor;

uniform sampler2D albedo;

void main(){
    FragColor = vec4(texture(albedo, fs_texcoord).xyz, 1.0f);
};