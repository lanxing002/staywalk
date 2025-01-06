#version 330 core

// input data layout
in vec3 norm;
in vec2 texcoord;
in vec3 tangent;
in vec3 bitangent;
in vec3 light_pos;

// output data layout
out vec4 frag_color;  
uniform sampler2D diffuse;
uniform sampler2D shadow;
uniform vec4 light;

// shader code

void main(){
    vec3 n = normalize(norm); 
    vec3 c = texture(diffuse, texcoord).xyz;  
    float d = texture(shadow, light_pos.xy).x;
    //float factor = dot(n, vec3(1, 1, 0.5));
    //frag_color.xyz = vec3(1.0, 1.0, 1.0);
    //frag_color.xyz = light.xyz * 1.0;
    frag_color.xyz = c;
    float s = (d + 0.001) < frag_color.z ? 0.0 : 1.0;
    frag_color.xyz *= s;
    frag_color.w = 1.0;
}