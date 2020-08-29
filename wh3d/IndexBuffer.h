#pragma once
#include "BindBase.h"
class IndexBuffer : BindBase
{
public:
	const unsigned short indices[12];
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC ibd ;
	D3D11_SUBRESOURCE_DATA isd ;
public:
	void CreateBuffer(Graphics& gfx);
	void Updata(Graphics& gfx);
};