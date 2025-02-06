// "common/deffered_common.vs"

void vs_main(inout OutBlock out_data)
{ 
    out_data.world_pos = u_model * vec4(vs_pos, 1.0);
    out_data.norm = vs_norm;
    out_data.texcoord = vs_texcoord;
    out_data.tangent = vs_tangent;
    out_data.bitangent = vs_bitangent;
}
 
 