
uniform sampler2D diffuse;

vec4 get_albedo(){
    return texture(diffuse, fs_texcoord); 
}

vec3 get_normal(){
    return normalize((fs_norm + 1.0) * 0.5);
}