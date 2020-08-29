#pragma once
#include"BindBase.h"
class ConstBuffer :BindBase
{
public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constBuffer;
	D3D11_BUFFER_DESC cbd;
	D3D11_SUBRESOURCE_DATA csd;
	struct ConstantBuffer
	{
		DirectX::XMMATRIX transform;
	};
public:
	void Updata(Graphics& gfx);
	
};