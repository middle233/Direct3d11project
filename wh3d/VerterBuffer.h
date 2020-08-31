#pragma once
#include "BindBase.h"
class VerterBuffer :BindBase
{
public:
	const UINT stride;
	const UINT offset;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd ;
	D3D11_SUBRESOURCE_DATA sd ;
public:
	template<class V>
	VerterBuffer(Graphics& gfx,const std::vector<V>& vertices);
	void Bind(Graphics& gfx) override;
};

