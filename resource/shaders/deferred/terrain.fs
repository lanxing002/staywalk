
uniform sampler2D height_tex;

vec4 get_albedo(){
    return vec4(0.8, 0.6, 0.4, 1.0);
}

vec3 get_normal(){
    vec2 tsize = textureSize(height_tex, 0);
    float step = 1.0 / tsize.x ;
    float hx1 = texture(height_tex, fs_texcoord + vec2(-step, .0)).x;
    float hx2 = texture(height_tex, fs_texcoord + vec2(step, .0)).x;
    float hy1 = texture(height_tex, fs_texcoord + vec2(.0, -step)).x;
    float hy2 = texture(height_tex, fs_texcoord + vec2(.0, +step)).x;

    vec3 vx = vec3((hx2 - hx1)/ (step * 2.0), 0.0, 1.0);
    vec3 vy = vec3(0.0, (hy2 - hy1)/ (step * 2.0), 1.0);
    return normalize(vx + vy);
}
