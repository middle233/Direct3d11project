#pragma once
#include"BindBase.h"
class PixelBuffer :BindBase
{
public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constbuffer2;
	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		}face_color[12];

	};
	const ConstantBuffer2 cb2;
	D3D11_BUFFER_DESC cbd2;
	D3D11_SUBRESOURCE_DATA csd2;
public:
	void CreateBuffer(Graphics& gfx);
	void UpData(Graphics& gfx);
};

