#pragma once
#include"BindBase.h"
class Topology:public BindBase
{
public:
	//���D3D11_PRIMITIVE_TOPOLOGY ��ָ��Ⱦ���˼������ͣ�����㣬�ߣ�����
	Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type);
	void Bind(Graphics& gfx) override;
protected:
	D3D11_PRIMITIVE_TOPOLOGY type;

};

