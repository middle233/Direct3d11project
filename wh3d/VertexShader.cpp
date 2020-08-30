#include "VertexShader.h"

VertexShader::VertexShader(Graphics& gfx)
{
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	GetDevice(gfx)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
}

void VertexShader::Bind(Graphics& gfx)
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}
