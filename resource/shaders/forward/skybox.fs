#version 330 core

in vec3 tex_coords;

out vec4 FragColor;

uniform samplerCube skybox;

// shader code
void main(){
    FragColor = texture(skybox, vec3(-tex_coords.x, tex_coords.y, -tex_coords.z));
}

