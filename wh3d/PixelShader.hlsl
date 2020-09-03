cbuffer CBuf
{
	float4 face_color[12];
};

float4 main(uint tid: SV_PrimitiveID ) : SV_TARGET
{
	return face_color[tid/2];
}