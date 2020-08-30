#pragma once
#include<cstddef>
#include"BindBase.h"
class InputLayout :BindBase
{
public:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[];
public:
	void Bind(Graphics& gfx) override;
	InputLayout(Graphics& gfx);
};