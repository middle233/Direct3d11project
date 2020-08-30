#include "VerterBuffer.h"

VerterBuffer::VerterBuffer(Graphics& gfx):
	vertices{
		{ 0.5f, 0.5f, 0.5f},
		{ 0.5f,-0.5f, 0.5f},
		{-0.5f,-0.5f, 0.5f},
		{-0.5f, 0.5f, 0.5f},
		{ 0.5f, 0.5f,-0.5f},
		{ 0.5f,-0.5f,-0.5f},
		{-0.5f,-0.5f,-0.5f},
		{-0.5f, 0.5f,-0.5f},
	},
	bd {},
	sd{},
	stride(sizeof(Vertex)),
	offset(0u)
{

	ZeroMemory(&bd, sizeof(bd));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);

	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertices;

	GetDevice(gfx)->CreateBuffer(&bd, &sd, pVertexBuffer.GetAddressOf());
}

void VerterBuffer::Bind(Graphics& gfx)
{
	GetContext(gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}
