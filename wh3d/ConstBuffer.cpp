#include "ConstBuffer.h"

void ConstBuffer::Updata(Graphics& gfx)
{
	GetDevice(gfx)->CreateBuffer(&cbd, &csd, constBuffer.GetAddressOf());
	GetContext(gfx)->VSSetConstantBuffers(0u, 1u, constBuffer.GetAddressOf());
}