#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics& gfx,const std::vector<unsigned short>& indices)
	:
	count((UINT)indices.size())
	
{
	D3D11_BUFFER_DESC cbd = {};
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.CPUAccessFlags = 0u;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(indices);
	cbd.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA csd;
	ZeroMemory(&csd, sizeof(csd));
	csd.pSysMem = indices.data();

	GetDevice(gfx)->CreateBuffer(&cbd, &csd, pIndexBuffer.GetAddressOf());

}

void IndexBuffer::Bind(Graphics& gfx)
{
	GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

UINT IndexBuffer::GetCount() const
{
	return count;
}
