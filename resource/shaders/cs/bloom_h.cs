#version 430 core

// must 256

layout (local_size_x =256, local_size_y = 1, local_size_z = 1) in;

// ----------------------------------------------------------------------------
// uniforms
// ----------------------------------------------------------------------------

layout(rgba16f, binding = 0) uniform image2D input_img;
layout(rgba16f, binding = 1) uniform image2D output_img;
layout(rgba16f, binding = 2) uniform image2D bloom_output_img;

// ----------------------------------------------------------------------------
// shared memory
// ----------------------------------------------------------------------------

shared vec4 scan_line[260];  // 256 + 4

// ----------------------------------------------------------------------------
//
// functions
//
// ----------------------------------------------------------------------------

void main() {
    const float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
    ivec2 in_img_size = imageSize(input_img);
	ivec2 tex_coord = ivec2(gl_GlobalInvocationID.xy);
    
    ivec2 local_tex_coord = ivec2(tex_coord.x % 256, tex_coord.y);
    scan_line[local_tex_coord.x] = imageLoad(input_img, tex_coord);
	imageStore(output_img, tex_coord, scan_line[local_tex_coord.x]);

    barrier();

    if(gl_LocalInvocationID.x == 0){
        ivec2 tex_border = ivec2(gl_WorkGroupID.x * 256 + 256,  tex_coord.y);
        scan_line[256] = imageLoad(input_img, tex_border + ivec2(0, 0));
        scan_line[257] = imageLoad(input_img, tex_border + ivec2(1, 0));
        scan_line[258] = imageLoad(input_img, tex_border + ivec2(2, 0));
        scan_line[259] = imageLoad(input_img, tex_border + ivec2(3, 0));
    
        for(int i = 0; i < 260; i++){
            float brightness = dot(scan_line[i].xyz, vec3(0.2126, 0.7152, 0.0722));
            if(brightness > 1.0) scan_line[i] = scan_line[i];
            else scan_line[i] = vec4(0.0, 0.0, 0.0, 1.0);
            scan_line[i] = brightness > 1.0 ? scan_line[i] : vec4(0.0, 0.0, 0.0, 1.0);
        }
    }

    barrier();

    vec4 result = scan_line[local_tex_coord.x] * weight[0];
    for(int i = 1 ; i < 5; i ++){
        int x = clamp(local_tex_coord.x + i, 0, 259);
        result += scan_line[x] * weight[i];
    }

    for(int i = 1; i < 5; i ++){
        int x = clamp(local_tex_coord.x - i, 0, 259);
        result += scan_line[x] * weight[i];
    }

    result.w = 1.0;
	imageStore(bloom_output_img, tex_coord, result);
}