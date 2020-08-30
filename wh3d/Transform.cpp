#include "Transform.h"

Transform::Transform(Graphics& gfx,int mouseY,int mouseX):
	cb{
		{
			DirectX::XMMatrixTranspose
			(
				DirectX::XMMatrixRotationZ(mouseY / 100) *
				DirectX::XMMatrixRotationY(mouseX / 100) *
				//DirectX::XMMatrixTranslation(mouseX/vpWidth*2-1,-mouseY/vpHeight*2+1,4.0f)*
				DirectX::XMMatrixTranslation(0.0f,0.0f ,mouseY / 100 + 4.0f) *
				DirectX::XMMatrixPerspectiveLH(1.0f,3.0f / 4.0f,0.5f,10.0f)
			)
		}
	}
{
	cbd={},
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;

	csd={},
	ZeroMemory(&csd, sizeof(csd));
	csd.pSysMem = &cb;

	GetDevice(gfx)->CreateBuffer(&cbd, &csd, constBuffer.GetAddressOf());
}

void Transform::Bind(Graphics& gfx)
{
	GetContext(gfx)->VSSetConstantBuffers(0u, 1u, constBuffer.GetAddressOf());
}
