
vec4 get_albedo(){
    return vec4(120.0, 0.2, 0.8, 1.0); 
}

vec3 get_normal(){
    return normalize((fs_norm + 1.0) * 0.5);
}