#version 330 core

// input data layout
layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_norm;
layout(location = 2) in vec2 in_texcoord;
layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_bitangent;
// layout(location = 5) in ivec4 boneIds; 
// layout(location = 6) in vec4 weights;

// out data layout
out vec3 norm;
out vec2 texcoord;
out vec3 tangent;
out vec3 bitangent;
out vec3 light_pos;


// uniform 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 light_view_project;


uniform sampler2D height;
// shader code
void main(){
    norm = in_norm;
    texcoord = in_texcoord;
    tangent = in_tangent;
    bitangent = in_bitangent;

    float h = textureLod(height, in_texcoord, 0.0).x;    
    vec4 world_pos = model * vec4(in_pos, 1.0);
    world_pos.z = h * 5.0;

    vec4 lpos = light_view_project * world_pos;
    lpos /= lpos.w;
    lpos = (lpos + 1.0) * 0.5;
    light_pos = lpos.xyz;

    gl_Position = projection * view * world_pos;
}

