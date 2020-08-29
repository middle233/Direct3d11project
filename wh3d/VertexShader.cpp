#include "VertexShader.h"

void VertexShader::CreateVertexShader(Graphics& gfx)
{
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	GetDevice(gfx)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
}

void VertexShader::UpData(Graphics& gfx)
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}
