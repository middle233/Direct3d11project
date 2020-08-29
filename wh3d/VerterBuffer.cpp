#include "VerterBuffer.h"

void VerterBuffer::CreateBuffer(Graphics& gfx)
{
	Vertex vertices[] =
	{
		{ 0.5f, 0.5f, 0.5f},
		{ 0.5f,-0.5f, 0.5f},
		{-0.5f,-0.5f, 0.5f},
		{-0.5f, 0.5f, 0.5f},
		{ 0.5f, 0.5f,-0.5f},
		{ 0.5f,-0.5f,-0.5f},
		{-0.5f,-0.5f,-0.5f},
		{-0.5f, 0.5f,-0.5f},

	};
	bd = {};
	ZeroMemory(&bd, sizeof(bd));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);

	sd = {};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertices;

	GetDevice(gfx)->CreateBuffer(&bd, &sd, pVertexBuffer.GetAddressOf());
}

void VerterBuffer::UpData(Graphics& gfx)
{
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;

	GetContext(gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}
