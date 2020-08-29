#include "InputLayout.h"

void InputLayout::CreateInputLayout(Graphics& gfx)
{
	GetDevice(gfx)->CreateInputLayout(
		ied,
		(UINT)std::size_t(ied),//这里找不到std::size使用了size_t
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	);
	
}

void InputLayout::UpData(Graphics& gfx)
{
	GetContext(gfx)->IASetInputLayout(pInputLayout.Get());
}

InputLayout::InputLayout(Graphics& gfx)
	:
	ied{ {
			"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0
		} }
{
	CreateInputLayout(gfx);
	UpData(gfx);
}
