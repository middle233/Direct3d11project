#include "BindBase.h"

ID3D11DeviceContext* BindBase::GetContext(Graphics& gfx)
{
	return gfx.pcontext.Get();
}

ID3D11Device* BindBase::GetDevice(Graphics& gfx)
{
	return gfx.pDevice.Get();
}
