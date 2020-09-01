#pragma once
#include"Graphics.h"

//#include"BindBase.h"
class BindBase;
class DrawBase
{

public:
	DrawBase() = default;
	DrawBase(const DrawBase&) = delete;
	virtual DirectX::XMMATRIX GetTransformXM() const = 0;
	void Draw(Graphics& gfx)const;
	virtual void Updata(float dt) = 0;
	void AddBind(std::unique_ptr<BindBase> bind);
	void AddIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf);
	virtual ~DrawBase() = default;
private:
	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<BindBase>> binds;
};

