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
    vec3 n = normalize(norm);   
    //float factor = dot(n, vec3(1, 1, 0.5));
    //frag_color.xyz = vec3(1.0, 1.0, 1.0);
    frag_color.xyz = norm;
    frag_color.w = 1.0;
}