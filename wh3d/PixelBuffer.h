#pragma once
#include"ConstBuffer.h"
class PixelBuffer :ConstBuffer
{
public:
	struct ConstantBuffer
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		}face_color[12];

	};
	const ConstantBuffer cb;
public:
	PixelBuffer(Graphics& gfx);
	void Bind(Graphics& gfx) override;
};

