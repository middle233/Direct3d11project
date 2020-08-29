#include "PixelBuffer.h"

void PixelBuffer::CreateBuffer(Graphics& gfx)
{
	const ConstantBuffer2 cb2 =
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
	cbd2 = {};
	ZeroMemory(&cbd2, sizeof(cbd2));
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.Usage = D3D11_USAGE_DEFAULT;
	cbd2.CPUAccessFlags = 0u;
	cbd2.MiscFlags = 0u;
	cbd2.ByteWidth = sizeof(cb2);
	cbd2.StructureByteStride = 0u;

	csd2 = {};
	ZeroMemory(&csd2, sizeof(csd2));
	csd2.pSysMem = &cb2;

	GetDevice(gfx)->CreateBuffer(&cbd2, &csd2, constbuffer2.GetAddressOf());
}

void PixelBuffer::UpData(Graphics& gfx)
{
	GetContext(gfx)->PSSetConstantBuffers(0u, 1u, constbuffer2.GetAddressOf());
}
