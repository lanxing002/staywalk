
vec4 get_albedo(){
    return vec4(7.0, .4, .0, 1.0); 
}

vec3 get_normal(){
    return normalize((fs_norm + 1.0) * 0.5);
}