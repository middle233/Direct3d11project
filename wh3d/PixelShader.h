#pragma once
#include"BindBase.h"
#include<d3dcompiler.h>
#pragma comment(lib,"D3DCompiler.lib")
class PixelShader :public BindBase
{
public:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
public:
	PixelShader(Graphics& gfx,const std::wstring& path);
	void Bind(Graphics& gfx) override;
};