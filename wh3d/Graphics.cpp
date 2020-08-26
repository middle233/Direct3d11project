#include "Graphics.h"
#include<d3dcompiler.h>
#include"DrawTestTriangle.h"
#include"Window.h"
#include<DirectXMath.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")
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
	
}

void Graphics::EndFrame()
{
	pSwap->Present(1u, 0u);//第一个可以每秒60帧设置为1,每秒30帧为2，最高为4，第二个是falgs，不设置为0。
}
void Graphics::ClearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red,green,blue };
	pcontext->ClearRenderTargetView(pTarget.Get(), color);
}

void Graphics::DrawTestTriangle(float angle, float mouseX, float mouseY)
{
	
	namespace wrl = Microsoft::WRL;
	namespace dx = DirectX;
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		}pos;
	};
	//顶点
	Vertex vertices[] =
	{
		{ 0.5f, 0.5f, 0.5f},
		{ 0.5f,-0.5f, 0.5f},
		{-0.5f,-0.5f, 0.5f},
		{-0.5f, 0.5f, 0.5f},
		{ 0.5f, 0.5f,-0.5f},
		{ 0.5f,-0.5f,-0.5f},
		{-0.5f,-0.5f,-0.5f},
		{-0.5f, 0.5f,-0.5f},

	};

#pragma region  CreateVertexBuffer and bind

	//定义一个buffer类型的指针
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	
	//描述这个buffer是什么类型
	D3D11_BUFFER_DESC bd = {};
	ZeroMemory(&bd, sizeof(bd));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);

	//填充这个buffer的确切数据
	D3D11_SUBRESOURCE_DATA sd = {};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertices;

	//创建这个buffer，并pDevice指向buffer
	MYWMD_EXCEPT( pDevice->CreateBuffer(&bd, &sd,pVertexBuffer.GetAddressOf()));
		
#pragma endregion

#pragma region CreateIndexBuffer
	const unsigned short indices[] =
	{
		0,2,1,
		0,3,2,
		0,7,3,
		0,4,7,
		0,1,5,
		0,5,4,
		6,5,1,
		6,1,2,
		6,2,3,
		6,3,7,
		6,7,4,
		6,4,5
	};
	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC ibd = {};
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(indices);
	ibd.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA isd = {};
	ZeroMemory(&isd, sizeof(isd));
	isd.pSysMem = indices;

	pDevice->CreateBuffer(&ibd, &isd, pIndexBuffer.GetAddressOf());

	pcontext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
#pragma endregion

#pragma region CreateConstBuffer
	struct ConstantBuffer
	{
		dx::XMMATRIX transform;
	};
	ConstantBuffer cb =
	{
		{
			dx::XMMatrixTranspose
			(
				dx::XMMatrixRotationZ(mouseY/100)*
				dx::XMMatrixRotationY(mouseX/100)*
				//dx::XMMatrixTranslation(mouseX/vpWidth*2-1,-mouseY/vpHeight*2+1,4.0f)*
				dx::XMMatrixTranslation(0.0f,0.0f ,4.0f)*
				dx::XMMatrixPerspectiveLH(1.0f,3.0f/4.0f,0.5f,10.0f)
			)
		}
	};
	wrl::ComPtr<ID3D11Buffer> constBuffer;
	D3D11_BUFFER_DESC cbd = {};
	ZeroMemory(&ibd, sizeof(cbd));
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA csd = {};
	ZeroMemory(&csd, sizeof(csd));
	csd.pSysMem =&cb ;

	pDevice->CreateBuffer(&cbd, &csd, constBuffer.GetAddressOf());

	pcontext->VSSetConstantBuffers(0u, 1u, constBuffer.GetAddressOf());
#pragma endregion

#pragma region CreateConstbuffer2
	wrl::ComPtr<ID3D11Buffer> constbuffer2;
	struct ConstantBuffer2
	{
		struct 
		{
			float r;
			float g;
			float b;
			float a;
		}face_color[12];

	};
	const ConstantBuffer2 cb2 = 
	{
		{
			{1.0f,0.0f,0.0f,1.0f},//R
			{0.75f,0.0f,0.0f,1.0f},//G
			{0.5f,0.0f,0.0f,1.0f},//B
			{0.25f,0.0f,0.0f,1.0f},//y
			{0.0f,1.0f,0.0f,1.0f},//
			{0.0f,0.75f,0.0f,1.0f},
			{0.0f,0.5f,0.0f,1.0f},
			{0.0f,0.25f,0.0f,1.0f},
			{0.0f,0.0f,1.0f,1.0f},
			{0.0f,0.0f,0.75f,1.0f},
			{0.0f,0.0f,0.5f,1.0f},
			{0.0f,0.0f,0.25f,1.0f},
		}
	};

	D3D11_BUFFER_DESC cbd2 = {};
	ZeroMemory(&cbd2, sizeof(cbd2));
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.Usage = D3D11_USAGE_DEFAULT;
	cbd2.CPUAccessFlags = 0u;
	cbd2.MiscFlags = 0u;
	cbd2.ByteWidth = sizeof(cb2);
	cbd2.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA csd2 = {};
	ZeroMemory(&csd2, sizeof(csd2));
	csd2.pSysMem = &cb2;

	pDevice->CreateBuffer(&cbd2, &csd2, constbuffer2.GetAddressOf());
	pcontext->PSSetConstantBuffers(0u, 1u, constbuffer2.GetAddressOf());
#pragma endregion

	//建立顶点缓冲区到渲染管线
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	
	//插槽为0，buffer数量为1，
	pcontext-> IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
	
	//设置三角形的边的渲染模式
	pcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	wrl::ComPtr<ID3DBlob> pBlob;

#pragma region Create a pixelshader
	//创建一个像素着色器
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	MYWMD_EXCEPT(D3DReadFileToBlob(L"PixelShader.cso", &pBlob));

	MYWMD_EXCEPT(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));

	//绑定像素着色器到渲染管线
	pcontext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
#pragma endregion

#pragma region Create a Vertexshader
	//创建一个顶点着色器
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	MYWMD_EXCEPT(D3DReadFileToBlob(L"VertexShader.cso", &pBlob));

	MYWMD_EXCEPT(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader));

	//顶点着色器绑定到渲染管线
	pcontext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
#pragma endregion

#pragma region Create a InputLayout

	//输出输出布局layout 创建一个Inputlayout指针 定义参数 创建InputLayout，绑定Inputlayout
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	//顶点着色中的POSITION,POSITION0,两种float R G,绑定的插槽上面的是0这个也是0,（offset这个元素从第几个字节开始，前面其他元素占了多少就是多少）,?,?)
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	MYWMD_EXCEPT(pDevice->CreateInputLayout(
		ied,
		(UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	));

	//绑定一个vertex layout
	pcontext->IASetInputLayout(pInputLayout.Get());
#pragma endregion
	//绑定一个render target,渲染目标？
	pcontext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), nullptr);

	//设置视口 viewport
	D3D11_VIEWPORT vp;
	vp.Width = vpWidth;
	vp.Height = vpHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pcontext->RSSetViewports(1u, &vp);
	
	//绘制顶点数，从第一个0开始画
	pcontext->DrawIndexed((UINT)std::size(indices),0u,0u);
}
