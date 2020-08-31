#include "InputLayout.h"

void InputLayout::Bind(Graphics& gfx)
{
	GetContext(gfx)->IASetInputLayout(pInputLayout.Get());
}

InputLayout::InputLayout(Graphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pBlob)

{
	GetDevice(gfx)->CreateInputLayout(
		layout.data(),
		layout.size(),//�����Ҳ���std::sizeʹ����size_t
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	);
	Bind(gfx);
}
