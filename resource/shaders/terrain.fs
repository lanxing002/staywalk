#version 330 core

// input data layout
in vec3 norm;
in vec2 texcoord;
in vec3 tangent;
in vec3 bitangent;
in vec3 light_pos;


// output data layout
out vec4 frag_color;  
// uniform sampler2D height;
uniform sampler2D height;
uniform sampler2D shadow;
 

// shader code  

void main(){
    vec3 light = normalize(vec3(0.3, 0.2, 0.9));
    vec3 color = texture(height, texcoord).rrr;

    float d = texture(shadow, light_pos.xy).x;
    float s = (d + 0.0002) < light_pos.z ? 0.0 : 1.0;

    
    vec2 tsize = textureSize(height, 0);
    float step = 1.0 / tsize.x ;
    float hx1 = texture(height, texcoord + vec2(-step, .0)).x;
    float hx2 = texture(height, texcoord + vec2(step, .0)).x;
    float hy1 = texture(height, texcoord + vec2(.0, -step)).x;
    float hy2 = texture(height, texcoord + vec2(.0, +step)).x;

    vec3 vx = vec3((hx2 - hx1)/ (step * 2.0), 0.0, 1.0);
    vec3 vy = vec3(0.0, (hy2 - hy1)/ (step * 2.0), 1.0);
    vec3 n = normalize(vx + vy);
    float f = dot(n, light);
    frag_color.z = 1.0; 
    frag_color.xyz = vec3(f) * vec3(0.8, 0.6, 0.4);
    frag_color.xyz *= s;
    frag_color.w = 1.0;
}