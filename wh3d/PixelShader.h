#pragma once
#include"BindBase.h"
#include<d3dcompiler.h>
#pragma comment(lib,"D3DCompiler.lib")
class PixelShader :BindBase
{
public:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
public:
	void CreatePixelShader(Graphics& gfx);
	void UpData(Graphics& gfx);
};