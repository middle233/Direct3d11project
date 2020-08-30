#pragma once
#include "ConstBuffer.h"
class Transform :ConstBuffer
{
public:
	struct ConstantBuffer
	{
		DirectX::XMMATRIX transform;
	};
	ConstantBuffer cb;
public:
	Transform(Graphics& gfx, int mouseY, int mouseX);
	void Bind(Graphics& gfx) override;
};

