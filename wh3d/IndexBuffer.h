#pragma once
#include "BindBase.h"
class IndexBuffer : public BindBase
{
public:
	UINT count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
public:
	IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indices);
	void Bind(Graphics& gfx) override;
	UINT GetCount() const;
};