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

shared vec4 scan_line[256];

// ----------------------------------------------------------------------------
//
// functions
//
// ----------------------------------------------------------------------------

void main() {
    float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

    ivec2 in_img_size = imageSize(input_img);
    ivec2 out_img_size = imageSize(input_img);

	ivec2 tex_coord = ivec2(gl_GlobalInvocationID.xy);

    scan_line[tex_coord.x % 256] = imageLoad(input_img, tex_coord);
    barrier();
    vec4 result = max(scan_line[tex_coord.x % 256], 0.0);
    result.w = 1.0;
	imageStore(output_img, tex_coord, result);
}