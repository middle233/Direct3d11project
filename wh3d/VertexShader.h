#pragma once
#include"BindBase.h"
#include<d3dcompiler.h>
#pragma comment(lib,"D3DCompiler.lib")
class VertexShader :BindBase
{
public:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
public:
	VertexShader(Graphics& gfx);
	void Bind(Graphics& gfx) override;
};