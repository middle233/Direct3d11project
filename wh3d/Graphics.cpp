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
	
}

void Graphics::EndFrame()
{
	pSwap->Present(1u, 0u);//��һ������ÿ��60֡����Ϊ1,ÿ��30֡Ϊ2�����Ϊ4���ڶ�����falgs��������Ϊ0��
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
	//����
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

	//����һ��buffer���͵�ָ��
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	
	//�������buffer��ʲô����
	D3D11_BUFFER_DESC bd = {};
	ZeroMemory(&bd, sizeof(bd));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);

	//������buffer��ȷ������
	D3D11_SUBRESOURCE_DATA sd = {};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertices;

	//�������buffer����pDeviceָ��buffer
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

	//�������㻺��������Ⱦ����
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	
	//���Ϊ0��buffer����Ϊ1��
	pcontext-> IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
	
	//���������εıߵ���Ⱦģʽ
	pcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	wrl::ComPtr<ID3DBlob> pBlob;

#pragma region Create a pixelshader
	//����һ��������ɫ��
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	MYWMD_EXCEPT(D3DReadFileToBlob(L"PixelShader.cso", &pBlob));

	MYWMD_EXCEPT(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));

	//��������ɫ������Ⱦ����
	pcontext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
#pragma endregion

#pragma region Create a Vertexshader
	//����һ��������ɫ��
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	MYWMD_EXCEPT(D3DReadFileToBlob(L"VertexShader.cso", &pBlob));

	MYWMD_EXCEPT(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader));

	//������ɫ���󶨵���Ⱦ����
	pcontext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
#pragma endregion

#pragma region Create a InputLayout

	//����������layout ����һ��Inputlayoutָ�� ������� ����InputLayout����Inputlayout
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	//������ɫ�е�POSITION,POSITION0,����float R G,�󶨵Ĳ���������0���Ҳ��0,��offset���Ԫ�شӵڼ����ֽڿ�ʼ��ǰ������Ԫ��ռ�˶��پ��Ƕ��٣�,?,?)
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

	//��һ��vertex layout
	pcontext->IASetInputLayout(pInputLayout.Get());
#pragma endregion
	//��һ��render target,��ȾĿ�ꣿ
	pcontext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), nullptr);

	//�����ӿ� viewport
	D3D11_VIEWPORT vp;
	vp.Width = vpWidth;
	vp.Height = vpHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pcontext->RSSetViewports(1u, &vp);
	
	//���ƶ��������ӵ�һ��0��ʼ��
	pcontext->DrawIndexed((UINT)std::size(indices),0u,0u);
}
