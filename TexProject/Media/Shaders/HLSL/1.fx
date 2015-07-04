//float4x4 mvp;

struct VS_OUTPUT 
{
   float4 Pos: POSITION;
   //float2 TexCoord: TEXCOORD0; 
};


VS_OUTPUT VS(float4 Pos: POSITION)
{
   VS_OUTPUT Out;
   Out.Pos = Pos;	//mul(mvp,Pos);
   //Out.TexCoord = normalize(Pos.xy);
   return Out;
}


float4 PS(): COLOR0
{
   return float4(1.0,1.0,1.0,1.0);
}


technique RenderScene
{
	pass P0
	{         
		VertexShader = compile vs_1_1 VS();
		PixelShader  = compile ps_1_1 PS();
	}
}
