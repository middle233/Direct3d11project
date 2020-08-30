#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics& gfx)
	:

	indices{
		0,2,1,
		0,3,2,
		0,7,3,
		0,4,7,
		0,1,5,
		0,5,4,
		6,5,1,
		6,1,2,
		6,2,3,
		6,3,7,
		6,7,4,
		6,4,5
}
{
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.CPUAccessFlags = 0u;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(indices);
	cbd.StructureByteStride = 0u;

	ZeroMemory(&csd, sizeof(csd));
	csd.pSysMem = indices;

	GetDevice(gfx)->CreateBuffer(&cbd, &csd, constBuffer.GetAddressOf());

}

void IndexBuffer::Bind(Graphics& gfx)
{
	GetContext(gfx)->IASetIndexBuffer(constBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}
