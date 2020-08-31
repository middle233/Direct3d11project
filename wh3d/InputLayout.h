#pragma once
#include<cstddef>
#include"BindBase.h"
class InputLayout :BindBase
{
public:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
public:
	void Bind(Graphics& gfx) override;
	InputLayout(Graphics& gfx,const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pBlob);
};