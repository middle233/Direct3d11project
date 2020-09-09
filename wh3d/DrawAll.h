#pragma once
#include"DrawBase.h"
#include"IndexBuffer.h"

template<class T>
class DrawAll :public DrawBase
{
private:
	static std::vector<std::unique_ptr<BindBase>> staticBinds;
private:
	const std::vector<std::unique_ptr<BindBase>>& GetStaticBinds() const override
	{
		return staticBinds;
	};
	
protected:
	static bool IsStaticInitialized() 
	{
		return !staticBinds.empty() ;
	}
	static void AddStaticBind(std::unique_ptr<BindBase> bind)
	{
		staticBinds.push_back(std::move(bind));
	}
	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> ibuf)
	{
		pIndexBuffer = ibuf.get();
		staticBinds.push_back(std::move(ibuf));
	}
	void SetIndexFromStatic()
	{
		for (const auto& b : staticBinds)
		{
			if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
			{
				pIndexBuffer = p;
				return;
			}
		}
	}
};

template<class T>
std::vector<std::unique_ptr<BindBase>> DrawAll<T>::staticBinds;
