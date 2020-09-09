#include "TransformCbuf.h"

TransformCbuf::TransformCbuf(Graphics& gfx, const DrawBase& parent)
	:
	
	parent(parent)
{
	if (!pVcbuf)
	{
		pVcbuf = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(gfx);
	}
}

void TransformCbuf::Bind(Graphics& gfx)
{
	pVcbuf->Updata(gfx, DirectX::XMMatrixTranspose(parent.GetTransformXM() * gfx.Getprojection()));
	pVcbuf->Bind(gfx);
}
std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> TransformCbuf::pVcbuf;