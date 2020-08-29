#pragma once
#include "BindBase.h"
class VerterBuffer :BindBase
{
public:
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		}pos;
	};
	const UINT stride;
	const UINT offset;
	Vertex vertices[8];
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd ;
	D3D11_SUBRESOURCE_DATA sd ;
public:
	void CreateBuffer(Graphics& gfx);
	void UpData(Graphics& gfx);
};

