#include "Graphics.h"
#include"Window.h"
#pragma comment(lib,"d3d11.lib")
Graphics::Graphics(HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Height = 600;
	sd.BufferDesc.Width = 800;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//ͨ������ģʽ��ѡ��8λRGBAͨ��
	sd.BufferDesc.RefreshRate.Numerator = 60;//ˢ���ʷ��ӣ�
	sd.BufferDesc.RefreshRate.Denominator = 1;//ˢ���ʷ�ĸ��
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;//δָ�����ţ�Ҳ���ǳ�������
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;//����ɨ����
	//bufferdesc �йػ�����
	sd.SampleDesc.Count = 1;//ǰ����������Ϊ1
	sd.SampleDesc.Quality = 0;//�����������Ϊ0���˴�δ���ÿ���ݣ����Բ���ʹ�õ�����ݻ�����
	//sample    ����ģʽ
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//ǰ����������Ⱦ���߽���Ⱦ������������
	sd.BufferCount = 1;//�󻺳�������Ϊ1
	sd.OutputWindow = hwnd;
	//�������
	sd.Windowed = true;//���ڻ�
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;//���롭������Ч����
	sd.Flags = 0;//û�б��



	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pcontext
	);
	Microsoft::WRL::ComPtr< ID3D11Resource> pBackBuffer;
	pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	pDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&pTarget
	);
#pragma region Zbuffer
//����Zbuffer��������Ⱦ˳��
	D3D11_DEPTH_STENCIL_DESC depthDesc = {};
	depthDesc.DepthEnable = true;
	depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDesc.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilState;
	pDevice->CreateDepthStencilState(&depthDesc, pDepthStencilState.GetAddressOf());

	pcontext->OMSetDepthStencilState(pDepthStencilState.Get(), 1u);
#pragma endregion

#pragma region ZDepthTextrue
	//�������ͼ
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthMaskTexture;
	D3D11_TEXTURE2D_DESC DepthTextureDesc = {};
	DepthTextureDesc.Width = vpWidth;
	DepthTextureDesc.Height = vpHeight;
	DepthTextureDesc.MipLevels = 1u;
	DepthTextureDesc.ArraySize = 1u;
	DepthTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;//ר������ȵ�D32
	DepthTextureDesc.SampleDesc.Count = 1u;//
	DepthTextureDesc.SampleDesc.Quality = 0u;//�����
	DepthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	pDevice->CreateTexture2D(&DepthTextureDesc, nullptr, &pDepthMaskTexture);
	
	CD3D11_DEPTH_STENCIL_VIEW_DESC depthSVDesc = {};
	depthSVDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthSVDesc.Texture2D.MipSlice = 0u;
	pDevice->CreateDepthStencilView(pDepthMaskTexture.Get(), &depthSVDesc, &pDepthStencilView);
	pcontext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDepthStencilView.Get());
#pragma endregion

#pragma region  SetViewPort
	//�����ӿ� viewport
	D3D11_VIEWPORT vp;
	vp.Width = vpWidth;
	vp.Height = vpHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pcontext->RSSetViewports(1u, &vp);
#pragma endregion

}

void Graphics::EndFrame()
{
	pSwap->Present(1u, 0u);//��һ������ÿ��60֡����Ϊ1,ÿ��30֡Ϊ2�����Ϊ4���ڶ�����falgs��������Ϊ0��
}

void Graphics::ClearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red,green,blue };
	pcontext->ClearRenderTargetView(pTarget.Get(), color);
	pcontext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::DrawIndexed(UINT uint)
{
	pcontext->DrawIndexed(uint, 0u, 0u);
}

void Graphics::SetProjection(DirectX::FXMMATRIX project) noexcept
{
	projection = project;
}

DirectX::XMMATRIX Graphics::Getprojection() const noexcept
{
	return projection;
}
