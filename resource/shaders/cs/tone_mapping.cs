#version 430 core

// must 256

layout (local_size_x =256, local_size_y = 1, local_size_z = 1) in;

// ----------------------------------------------------------------------------
// uniforms
// ----------------------------------------------------------------------------

layout(rgba16f, binding = 0) uniform image2D input_img;
layout(rgba16f, binding = 1) uniform image2D output_img;

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
    ivec2 in_img_size = imageSize(input_img);
    ivec2 out_img_size = imageSize(input_img);

	ivec2 tex_coord = ivec2(gl_GlobalInvocationID.xy);
    //tex_coord.x = min(tex_coord.x, in_img_size.x - 1);
    //tex_coord.x = min(tex_coord.x, out_img_size.x - 1);

    scan_line[tex_coord.x % 256] = imageLoad(input_img, tex_coord);
    barrier();

    vec3 mapped = scan_line[tex_coord.x % 256].xyz / (scan_line[tex_coord.x % 256].xyz + vec3(1.0));
    //vec4 result = max(scan_line[tex_coord.x % 256] - 1.0, 0.0);
    //result.xyz = vec3(100.0, .0, .0);
    // result.xyz = imageLoad(input_img, tex_coord).xxz;
    //result.xy = gl_GlobalInvocationID.xy / vec2(in_img_size);


    vec4 result = vec4(mapped, 1.0);
	imageStore(output_img, tex_coord, result);
} 