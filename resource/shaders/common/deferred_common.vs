#version 330 core

// input data layout
layout(location = 0) in vec3    vs_pos;
layout(location = 1) in vec3    vs_norm;
layout(location = 2) in vec2    vs_texcoord;
layout(location = 3) in vec3    vs_tangent;
layout(location = 4) in vec3    vs_bitangent;
layout(location = 5) in ivec4   vs_bone_ids; 
layout(location = 6) in vec4    vs_bone_weights;

vec3 fs_pos;  // for common name rules
vec3 fs_norm;
vec3 fs_tangent;
vec3 fs_bitangent;

// uniform 
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform mat4 nod_u_light_view_project;
uniform vec4 nod_u_light;
uniform bool nod_u_use_skeleton;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
layout (std140) uniform  nod_u_bone_matrices_block{
    mat4 nod_bone_matrices[MAX_BONES];
};


// out data layout
out vec3 nod_norm;
out vec2 nod_texcoord;
out vec3 nod_tangent;
out vec3 nod_bitangent;
out vec3 nod_light_view_pos;
out vec3 nod_world_pos;


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
    in_pos          = nod_in_pos;
    in_norm         = nod_in_norm;
    in_tangent      = nod_in_tangent;
    in_bitangent    = nod_in_bitangent;

    if(nod_u_use_skeleton){
        vec4 total_pos = vec4(0.0f);
        for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++){
            if(nod_in_bone_ids[i] == -1)  continue;
            if(nod_in_bone_ids[i] >=MAX_BONES) {
                total_pos = vec4(in_pos, 1.0f);
                break;
            }
            vec4 local_pos = nod_bone_matrices[nod_in_bone_ids[i]] * vec4(in_pos,1.0f);
            total_pos += local_pos * nod_in_bone_weights[i];
        }
    }

    OutBlock out_data;
    vs_main(out_data);

    nod_norm            = out_data.norm;
    nod_texcoord        = out_data.texcoord;
    nod_tangent         = out_data.tangent;
    nod_bitangent       = out_data.bitangent;
    nod_world_pos       = out_data.world_pos.xyz;

    nod_light_view_pos  = (nod_u_light_view_project * out_data.world_pos).xyz;
    gl_Position = u_projection * u_view * out_data.world_pos;
}


/**
vec2    in_texcoord;
vec3    in_pos; 
vec3    in_norm;
vec3    in_tangent;
vec3    in_bitangent;

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

