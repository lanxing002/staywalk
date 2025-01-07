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

float query_shaodw(){
    float d = texture(shadow, light_pos.xy).x;
    vec3 n = normalize(norm); 
    float bias = mix(0.0004, 0.00001, dot(n, light.xyz));
    float s = (d + bias) < light_pos.z ? 0.0 : 1.0;
    return s;
}

void main(){
    vec3 n = normalize(norm); 
    vec3 c = texture(diffuse, texcoord).xyz;  
    frag_color.xyz = c;
    frag_color.xyz *= query_shaodw();
    // frag_color.xyz = light.xyz;
    frag_color.w = 1.0;
}