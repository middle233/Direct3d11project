#include "Graphics.h"
#include"Window.h"
#pragma comment(lib,"d3d11.lib")
Graphics::Graphics(HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Height = 600;
	sd.BufferDesc.Width = 800;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//通道像素模式，选择8位RGBA通道
	sd.BufferDesc.RefreshRate.Numerator = 60;//刷新率分子？
	sd.BufferDesc.RefreshRate.Denominator = 1;//刷新率分母？
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;//未指明缩放，也就是充满窗口
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;//逐行扫描线
	//bufferdesc 有关缓冲区
	sd.SampleDesc.Count = 1;//前缓冲区数量为1
	sd.SampleDesc.Quality = 0;//锯齿消除设置为0，此处未设置抗锯齿，所以不会使用到抗锯齿缓冲区
	//sample    采样模式
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//前缓冲区，渲染管线将渲染其中所有内容
	sd.BufferCount = 1;//后缓冲区数量为1
	sd.OutputWindow = hwnd;
	//输出窗口
	sd.Windowed = true;//窗口化
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;//翻译……放弃效果？
	sd.Flags = 0;//没有标记



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
//创建Zbuffer，控制渲染顺序
	D3D11_DEPTH_STENCIL_DESC depthDesc = {};
	depthDesc.DepthEnable = true;
	depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDesc.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilState;
	pDevice->CreateDepthStencilState(&depthDesc, pDepthStencilState.GetAddressOf());

	pcontext->OMSetDepthStencilState(pDepthStencilState.Get(), 1u);
#pragma endregion

#pragma region ZDepthTextrue
	//创建深度图
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthMaskTexture;
	D3D11_TEXTURE2D_DESC DepthTextureDesc = {};
	DepthTextureDesc.Width = vpWidth;
	DepthTextureDesc.Height = vpHeight;
	DepthTextureDesc.MipLevels = 1u;
	DepthTextureDesc.ArraySize = 1u;
	DepthTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;//专用于深度的D32
	DepthTextureDesc.SampleDesc.Count = 1u;//
	DepthTextureDesc.SampleDesc.Quality = 0u;//抗锯齿
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
	//设置视口 viewport
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
	pSwap->Present(1u, 0u);//第一个可以每秒60帧设置为1,每秒30帧为2，最高为4，第二个是falgs，不设置为0。
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
