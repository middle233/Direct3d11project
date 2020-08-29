#include "PixelShader.h"

void PixelShader::CreatePixelShader(Graphics& gfx)
{
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
}

void PixelShader::UpData(Graphics& gfx)
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
