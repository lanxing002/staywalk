#version 330 core

// input data layout
layout(location = 0) in vec3 in_pos;

// uniform 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// shader code
void main(){

    gl_Position = projection * view *  model * vec4(in_pos, 1.0f);
    
}

