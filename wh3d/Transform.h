#pragma once
#include "BindBase.h"
class Transform :BindBase
{
public:
	struct ConstantBuffer
	{
		DirectX::XMMATRIX transform;
	};
	ConstantBuffer cb;
	Microsoft::WRL::ComPtr<ID3D11Buffer> constBuffer;
	D3D11_BUFFER_DESC cbd ;
	D3D11_SUBRESOURCE_DATA csd ;
public:
	void CreateBuffer(Graphics& gfx, int mouseY, int mouseX);
	void updata(Graphics& gfx);
};

