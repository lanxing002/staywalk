// "common/deffered_common.vs"

void vs_main(inout OutBlock out_data)
{
    out_data.world_pos = u_model * vec4(in_pos, 1.0);
    out_data.norm = in_norm;
    out_data.texcoord = in_texcoord;
    out_data.tangent = in_tangent;
    out_data.bitangent = in_bitangent;
}

