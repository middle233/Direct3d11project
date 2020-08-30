#pragma once
#include "ConstBuffer.h"
class IndexBuffer : ConstBuffer
{
public:
	const unsigned short indices[36];
public:
	IndexBuffer(Graphics& gfx);
	void Bind(Graphics& gfx) override;
};