#pragma once
#include"BindBase.h"

template<typename C>
class ConstBuffer :public BindBase
{
public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstBuffer;

public:
	void Updata(Graphics& gfx, const C& consts)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetContext(gfx)->Map(
			pConstBuffer.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD,
			0u, &msr);
		memcpy(msr.pData, &consts, sizeof(consts));
		GetContext(gfx)->Unmap(pConstBuffer.Get(), 0u);
	}
	//有顶点的构造函数
	ConstBuffer(Graphics& gfx, const C& consts)
	{
		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(consts);
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd;
		csd.pSysMem = &consts;
		GetDevice(gfx)->CreateBuffer(&cbd, &csd, &pConstBuffer);
	}
	//无顶点的构造
	ConstBuffer(Graphics& gfx)
	
	{
		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(C);
		cbd.StructureByteStride = 0u;
		GetDevice(gfx)->CreateBuffer(&cbd, nullptr, &pConstBuffer);
	}
};


template<typename C>
class VertexConstantBuffer:public ConstBuffer<C>
{
	using ConstBuffer<C>::pConstBuffer;
	using BindBase::GetContext;
public:
	using ConstBuffer<C>::ConstBuffer;
	void Bind(Graphics& gfx) override
	{
		GetContext(gfx)->VSSetConstantBuffers(0u, 1u, pConstBuffer.GetAddressOf());
	}
};


template<typename C>
class PixelConstantBuffer :public ConstBuffer<C>
{
	using ConstBuffer<C>::pConstBuffer;
	using BindBase::GetContext;
public:
	using ConstBuffer<C>::ConstBuffer;
	void Bind(Graphics& gfx) override
	{
		GetContext(gfx)->PSSetConstantBuffers(0u, 1u, pConstBuffer.GetAddressOf());
	}
};