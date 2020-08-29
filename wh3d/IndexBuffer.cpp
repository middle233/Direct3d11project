#include "IndexBuffer.h"

void IndexBuffer::CreateBuffer(Graphics& gfx)
{
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(indices);
	ibd.StructureByteStride = 0u;

	ZeroMemory(&isd, sizeof(isd));
	isd.pSysMem = indices;

	GetDevice(gfx)->CreateBuffer(&ibd, &isd, pIndexBuffer.GetAddressOf());

}

void IndexBuffer::Updata(Graphics& gfx)
{
	GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}
