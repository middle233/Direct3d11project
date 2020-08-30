#pragma once
#include"BindBase.h"
class ConstBuffer :protected BindBase
{
public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constBuffer;
	D3D11_BUFFER_DESC cbd;
	D3D11_SUBRESOURCE_DATA csd;
};