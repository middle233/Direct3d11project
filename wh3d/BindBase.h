#pragma once
#include"Graphics.h"
#include<DirectXMath.h>
#pragma comment(lib,"d3d11.lib")
class BindBase
{
public:
	virtual void Bind(Graphics& gfx) = 0;
	virtual ~BindBase() = default;
protected:
	static ID3D11DeviceContext* GetContext(Graphics& gfx);
	static ID3D11Device* GetDevice(Graphics& gfx);
};