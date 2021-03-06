#pragma once
#include"BindBase.h"
#include<d3dcompiler.h>
#pragma comment(lib,"D3DCompiler.lib")
class VertexShader :public BindBase
{
public:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
public:
	VertexShader(Graphics& gfx, const std::wstring& path);
	void Bind(Graphics& gfx) override;
	ID3DBlob* GetBytecode();
};