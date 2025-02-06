
#version 330 core
in vec2 fs_texcoord;	
out vec4 FragColor;

uniform sampler2D albedo;


const float PHI = 1.61803398874989484820459; // ¦µ = Golden Ratio 
const float seed = 12.0;

float gold_noise(in vec2 xy, in float seed)
{
    return fract(tan(distance(xy*PHI, xy)*seed)*xy.x);
}


void main(){
    float seed = fract(12.0); 
    vec3 noise = vec3(gold_noise(fs_texcoord * 1024.0, seed + 0.1), 
                      gold_noise(fs_texcoord * 1024.0, seed + 0.2),
                      gold_noise(fs_texcoord * 1024.0, seed + 0.3));
    FragColor = vec4(texture(albedo, fs_texcoord).xyz, 1.0f);
    // FragColor = vec4(noise + 2.0, 1.0f);
};