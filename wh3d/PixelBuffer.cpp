#include "PixelBuffer.h"

PixelBuffer::PixelBuffer(Graphics& gfx)
{
	const ConstantBuffer cb =
	{
		{
			{1.0f,0.0f,0.0f,1.0f},//R
			{0.75f,0.0f,0.0f,1.0f},//G
			{0.5f,0.0f,0.0f,1.0f},//B
			{0.25f,0.0f,0.0f,1.0f},//y
			{0.0f,1.0f,0.0f,1.0f},//
			{0.0f,0.75f,0.0f,1.0f},
			{0.0f,0.5f,0.0f,1.0f},
			{0.0f,0.25f,0.0f,1.0f},
			{0.0f,0.0f,1.0f,1.0f},
			{0.0f,0.0f,0.75f,1.0f},
			{0.0f,0.0f,0.5f,1.0f},
			{0.0f,0.0f,0.25f,1.0f},
		}
	};
	cbd = {};
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.CPUAccessFlags = 0u;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	
	csd = {};
	ZeroMemory(&csd, sizeof(csd));
	csd.pSysMem = &cb;
	
	GetDevice(gfx)->CreateBuffer(&cbd, &csd, constBuffer.GetAddressOf());
}

void PixelBuffer::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetConstantBuffers(0u, 1u, constBuffer.GetAddressOf());
}
