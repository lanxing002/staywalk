#version 330 core

// input data layout
in vec3 norm;
in vec2 texcoord;
in vec3 tangent;
in vec3 bitangent;

// output data layout
out vec4 frag_color;  
// uniform sampler2D height;
uniform sampler2D height;


// shader code  

void main(){
    vec3 n = normalize(norm);
    vec3 color = texture(height, texcoord).rrr;
    //float factor = dot(n, vec3(1, 1, 0.5));
    //frag_color.xyz = vec3(1.0, 1.0, 1.0);
    // frag_color.xyz = color * 0.2;
    frag_color.z = 1.0; 
    frag_color.xyz = color;
    frag_color.w = 1.0;
}