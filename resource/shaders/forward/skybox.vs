#version 330 core

// input data layout
layout(location = 0) in vec3 in_pos;

out vec3 tex_coords; 
uniform mat4 view;
uniform mat4 projection;

// shader code
void main(){
    tex_coords = in_pos;
    mat4 v = view;
    v[3] = vec4(0.0, 0.0, 0.0, 1.0);

    vec4 pos = projection * v * vec4(in_pos, 1.0);
    pos.z = pos.w - 0.00001;
    gl_Position = pos;  
}

