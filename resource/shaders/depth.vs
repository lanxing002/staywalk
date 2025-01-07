#version 330 core

// input data layout
layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_norm;
layout(location = 2) in vec2 in_texcoord;
layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_bitangent;
layout(location = 5) in ivec4 bone_ids; 
layout(location = 6) in vec4 bone_weights;

 
// uniform 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
layout (std140) uniform  BoneMatrixBlock {
    mat4 bone_matrices[100];
};

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;

// shader code
void main(){
    vec4 total_pos = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++){
        if(bone_ids[i] == -1)  continue;
        if(bone_ids[i] >=MAX_BONES) { 
            total_pos = vec4(in_pos, 1.0f);
            break;
        }
        vec4 local_pos = bone_matrices[bone_ids[i]] * vec4(in_pos,1.0f);
        total_pos += local_pos * bone_weights[i];
        //vec3 localNormal = mat3(bones_matrices[bone_ids[i]]) * norm;
   }
	
    gl_Position = projection * view * model * total_pos;
}

