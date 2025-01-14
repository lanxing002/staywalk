
uniform sampler2D height_tex;

void vs_main(inout OutBlock out_data)
{
    float h = textureLod(height_tex, in_texcoord, 0.0).x;    
    vec4 world_pos = u_model * vec4(in_pos, 1.0);
    world_pos.z = h * 5.0; 

    out_data.world_pos = world_pos;
    out_data.norm = in_norm;
    out_data.texcoord = in_texcoord;
    out_data.tangent = in_tangent;
    out_data.bitangent = in_bitangent;
}
