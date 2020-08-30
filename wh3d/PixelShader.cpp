#include "PixelShader.h"

 PixelShader::PixelShader(Graphics& gfx)
{
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
}

void PixelShader::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
