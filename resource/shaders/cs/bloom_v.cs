#version 430 core

// must 256

layout (local_size_x = 1, local_size_y = 256, local_size_z = 1) in;

// ----------------------------------------------------------------------------
// uniforms
// ----------------------------------------------------------------------------
layout(rgba16f, binding = 0) uniform image2D bloom_input_img;

layout(rgba16f, binding = 1) uniform image2D input_img;
layout(rgba16f, binding = 2) uniform image2D output_img;

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
    ivec2 in_img_size = imageSize(bloom_input_img);
	ivec2 tex_coord = ivec2(gl_GlobalInvocationID.xy);
    
    ivec2 local_tex_coord = ivec2(tex_coord.x, tex_coord.y % 256);
    scan_line[local_tex_coord.y] = imageLoad(bloom_input_img, tex_coord);

    if(gl_LocalInvocationID.y == 0){
        ivec2 tex_border = ivec2(tex_coord.x, gl_WorkGroupID.y * 256 + 256);
        scan_line[256] = imageLoad(bloom_input_img, tex_border + ivec2(0, 0));
        scan_line[257] = imageLoad(bloom_input_img, tex_border + ivec2(0, 1));
        scan_line[258] = imageLoad(bloom_input_img, tex_border + ivec2(0, 2));
        scan_line[259] = imageLoad(bloom_input_img, tex_border + ivec2(0, 3));
    }

    barrier();

    vec4 result = scan_line[local_tex_coord.y] * weight[0];
    for(int i = 1 ; i < 5; i ++){
        int x = clamp(local_tex_coord.y + i, 0, 259);
        result += scan_line[x] * weight[i];
    }

    for(int i = 1; i < 5; i ++){
        int x = clamp(local_tex_coord.y - i, 0, 259);
        result += scan_line[x] * weight[i];
    }

    result.w = 1.0;
	imageStore(output_img, tex_coord, result);
}