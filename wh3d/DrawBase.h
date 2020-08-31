#pragma once
#include"Graphics.h"
#include<DirectXMath.h>
#include <random>
class BindBase;
class DrawBase
{
private:
	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<BindBase>> binds;
public:
	DrawBase() = default;
	DrawBase(const DrawBase&) = delete;
	virtual DirectX::XMMATRIX GetTransformXM()const = 0;
	void Draw(Graphics& gfx)const;
	virtual void Updata(float dt) = 0;
	void AddBind(std::unique_ptr<BindBase> bind);
	void AddIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf);
	virtual ~DrawBase() = default;
};

