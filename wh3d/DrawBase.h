#pragma once
#include"Graphics.h"

//#include"BindBase.h"
class BindBase;
class DrawBase
{
	template<class T>
	friend class DrawAll;
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
	virtual const std::vector<std::unique_ptr<BindBase>>& GetStaticBinds() const =0;
private:
	const class IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<BindBase>> binds;
};

