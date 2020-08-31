#include "VerterBuffer.h"
template<class V>
VerterBuffer::VerterBuffer(Graphics& gfx, const std::vector<V>& vertices)
	:
	bd{},
	sd{},
	stride(sizeof(V)),
	offset(0u)
{

	ZeroMemory(&bd, sizeof(bd));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.ByteWidth = UINT (sizeof(v))*vertices.size());
	bd.StructureByteStride = sizeof(V);

	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertices.data();

	GetDevice(gfx)->CreateBuffer(&bd, &sd, pVertexBuffer.GetAddressOf());
}

void VerterBuffer::Bind(Graphics& gfx)
{
	GetContext(gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}
