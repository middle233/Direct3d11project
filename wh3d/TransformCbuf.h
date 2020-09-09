#pragma once
#include"ConstBuffer.h"
#include"DrawBase.h"
#include<DirectXMath.h>
class TransformCbuf:public BindBase
{
public:
	TransformCbuf(Graphics& gfx, const DrawBase& parent);
	void Bind(Graphics& gfx) override;
private:
	
	static std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> pVcbuf;
	const DrawBase& parent;
};


