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

// uniform 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform sampler2D height;


// shader code
void main(){
    float h = texture(height, texcoord).x;
    norm = in_norm;
    texcoord = in_texcoord;
    tangent = in_tangent;
    bitangent = in_bitangent;
    vec4 world_pos = model * vec4(in_pos, 1.0);
    world_pos.z = sin((in_pos.x + in_pos.y) * 4) * 100.0;
    world_pos.z = h * 10.0;
    gl_Position = projection * view * world_pos;
}

