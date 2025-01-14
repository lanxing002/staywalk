#version 330 core

// input data layout
layout(location = 0) in vec3    vs_pos;
layout(location = 1) in vec3    vs_norm;
layout(location = 2) in vec2    vs_texcoord;
layout(location = 3) in vec3    vs_tangent;
layout(location = 4) in vec3    vs_bitangent;
layout(location = 5) in ivec4   vs_bone_ids; 
layout(location = 6) in vec4    vs_bone_weights;


// uniform 
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform mat4 u_light_view_project;
uniform vec4 u_light;
uniform bool u_use_skeleton;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
layout (std140) uniform  u_bone_matrices_block{
    mat4 u_bone_matrices[MAX_BONES];
};


// out data layout
out vec3 fs_norm;
out vec2 fs_texcoord;
out vec3 fs_tangent;
out vec3 fs_bitangent;
out vec3 fs_light_view_pos;
out vec3 fs_world_pos;


struct OutBlock{
    vec4 world_pos;
    vec3 norm;
    vec2 texcoord;
    vec3 tangent;
    vec3 bitangent;
};



void vs_main(inout OutBlock out_data);

// shader code
void main(){
    if(u_use_skeleton){
        vec4 total_pos = vec4(0.0f);
        for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++){
            if(vs_bone_ids[i] == -1)  continue;
            if(vs_bone_ids[i] >= MAX_BONES) {
                total_pos = vec4(vs_pos, 1.0f);
                break;
            }
            vec4 local_pos = u_bone_matrices[vs_bone_ids[i]] * vec4(vs_pos,1.0f);
            total_pos += local_pos * vs_bone_weights[i];
        }
    }

    OutBlock out_data;
    vs_main(out_data);

    fs_norm            = out_data.norm;
    fs_texcoord        = out_data.texcoord;
    fs_tangent         = out_data.tangent;
    fs_bitangent       = out_data.bitangent;
    fs_world_pos       = out_data.world_pos.xyz;
    fs_light_view_pos  = (u_light_view_project * out_data.world_pos).xyz;

    gl_Position = u_projection * u_view * out_data.world_pos;
}


/**
vec2    vs_texcoord;
vec3    vs_pos; 
vec3    vs_norm;
vec3    vs_tangent;
vec3    vs_bitangent;

// uniform 
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

struct OutBlock{
    vec4 world_pos;
    vec3 norm;
    vec2 texcoord;
    vec3 tangent;
    vec3 bitangent;
};

// must define this function in other shader
void vs_main(inout OutBlock out_data);
*/
 
// ===================user code=======================

