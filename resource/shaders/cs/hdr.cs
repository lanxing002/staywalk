#version 430 core

// must 256

layout (local_size_x =256, local_size_y = 1, local_size_z = 1) in;

// ----------------------------------------------------------------------------
// uniforms
// ----------------------------------------------------------------------------

layout(rgba8, binding = 0) uniform image2D input_img;
layout(rgba8, binding = 1) uniform image2D output_img; 
layout(rgba8, binding = 1) uniform image2D output_img; 

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
	ivec2 tex_coord = ivec2(gl_GlobalInvocationID.xy);
    scan_line[pos.x] = imageLoad(input_img, tex_coord);
    barrier();


	value.x = mod(float(texelCoord.x) + t * speed, width) / (gl_NumWorkGroups.x * gl_WorkGroupSize.x);
	value.y = float(texelCoord.y)/(gl_NumWorkGroups.y*gl_WorkGroupSize.y);
	imageStore(imgOutput, texelCoord, value);
}