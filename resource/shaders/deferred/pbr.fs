
uniform sampler2D diffuse;

vec4 get_albedo(){
    return texture(diffuse, in_texcoord); 
}

vec3 get_normal(){
    return in_norm;
}