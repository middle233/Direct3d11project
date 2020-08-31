#include "TransformCbuf.h"

TransformCbuf::TransformCbuf(Graphics& gfx, const DrawBase& parent)
	:
	vcbuf(gfx),
	parent(parent)
{}

void TransformCbuf::Bind(Graphics& gfx)
{
	vcbuf.Updata(gfx, DirectX::XMMatrixTranspose(parent.GetTransformXM() * gfx.Getprojection()));
	vcbuf.Bind(gfx);
}
