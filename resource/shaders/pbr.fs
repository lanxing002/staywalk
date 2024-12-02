#version 330 core

// input data layout
in vec3 norm;
in vec2 texcoord;
in vec3 tangent;
in vec3 bitangent;

// output data layout
out vec4 frag_color;  


// shader code

void main(){
    frag_color.x = norm.x;
    frag_color.y = texcoord.x;
    frag_color.z = tangent.x;
    frag_color.w = bitangent.x;
}