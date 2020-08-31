#include "VertexShader.h"

VertexShader::VertexShader(Graphics& gfx, const std::wstring& path)
{
	D3DReadFileToBlob(path.c_str(), &pBlob);
	GetDevice(gfx)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
}

void VertexShader::Bind(Graphics& gfx)
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}
