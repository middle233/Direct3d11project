#pragma once
#include"MyWin.h"
#include<d3d11.h>
#include<wrl.h>
#include<sstream>
class Graphics
{
public:
	Graphics( HWND hwnd );
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics()=default;
	void EndFrame();//Ìø×ªÕâÒ»Ö¡
	void ClearBuffer(float red, float green, float blue) noexcept;
	void DrawTestTriangle(float angle,float mouseX,float mouseY);
private:
	float vpWidth=800;
	float vpHeight=600;
	Microsoft::WRL::ComPtr< ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr < IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr < ID3D11DeviceContext> pcontext;
	Microsoft::WRL::ComPtr< ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView;
};

