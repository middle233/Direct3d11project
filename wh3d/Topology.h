#pragma once
#include"BindBase.h"
class Topology:public BindBase
{
public:
	//这个D3D11_PRIMITIVE_TOPOLOGY 是指渲染拓扑几何类型，例如点，线，三角
	Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type);
	void Bind(Graphics& gfx) override;
protected:
	D3D11_PRIMITIVE_TOPOLOGY type;

};

