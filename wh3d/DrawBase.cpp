#include "DrawBase.h"
#include"IndexBuffer.h"
void DrawBase::Draw(Graphics& gfx) const
{
	for (auto& b : binds)
	{
		b->Bind(gfx);
	}
	gfx.DrawIndexed(pIndexBuffer->GetCount());
}

void DrawBase::AddBind(std::unique_ptr<BindBase> bind)
{
	assert("Must use AddIndexbuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
	binds.push_back(std::move(bind));
}

void DrawBase::AddIndexBuffer(std::unique_ptr<IndexBuffer> ibuf)
{
	assert("≥¢ ‘ÃÌº”µΩindex buffer" && pIndexBuffer == nullptr);
	pIndexBuffer = ibuf.get();
	binds.push_back(std::move(ibuf));
}
