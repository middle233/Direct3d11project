#include "Window.h"
#include<sstream>
#include"resource.h"

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
	:
	hInst( GetModuleHandle(nullptr ))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	//������ͼ��
	wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));
	wc.hInstance = GetInstance();
	wc.hbrBackground = nullptr;
	wc.hCursor = nullptr;
	wc.lpszClassName = GetName();
	wc.lpszMenuName = nullptr;
	//������ͼ��
	wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());//ע��һ��������
}
HINSTANCE Window::WindowClass::GetInstance() noexcept {
	return wndClass.hInst;
}
const char* Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}


Window::Window(int width, int height, const char* name) 
	:
	width(width),
	height(height)
{
	//���ڴ�������
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	//�쳣��
	if (!(AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)))
	{
		throw MYWMD_LAST_EXCEPT();
	};
	//throw MYWMD_LAST_EXCEPT();
	//throw MYWMD_EXCEPT(ERROR_ARENA_TRASHED);
	//throw std::runtime_error("����");
	//throw 12345656;
	hWnd = CreateWindow(
		WindowClass::GetName(),name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);
	//�쳣��û�д�������
	if (hWnd == nullptr) 
	{
		throw MYWMD_LAST_EXCEPT();
	}
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	pGfx = std::make_unique <Graphics>(hWnd);//����������ָ�� ��hWnd new��һ��graphics
}
Window::~Window() {
	DestroyWindow(hWnd);
}
void Window::SetTile(const std::string title)
{
	if (!SetWindowText(hWnd, title.c_str()))
	{
		throw "Set Tile failed";
	}

}
std::optional<int> Window::ProcessMessages()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return msg.wParam;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return {};
}
Graphics& Window::Gfx()
{
	return *pGfx;
}
LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
	if (msg == WM_NCCREATE) {
		//�������ڳɹ�������Ϣ��ǰ��NC�Ǵ����û����Ĵ��ڣ�
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);//reinterpret_castָ��ת�����������޹ص�����ת����������ͬ�ı���λ
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}
//message case
LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		//����ʧȥ�۽�
	case WM_KILLFOCUS:
		keyboard.ClaerState();
		mouse.Flush();
		break;
		//����ƶ�
	case WM_MOUSEMOVE:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		//��ק����ʱ������ϳ��˴������Լ�����λ��
		if (pt.x >= 0 && pt.x <= width && pt.y >= 0 && pt.y <= height)
		{
			mouse.OnMouseMove(pt.x, pt.y);
			if (!mouse.IsInWindow())
			{
				SetCapture(hWnd);
				mouse.OnMouseEnter();
			}
		}
		else
		{
			//�ڴ�������/�Ҽ��ͷź�Release����겶��
			if (wParam & (mouse.LeftIsPressed() | mouse.RightIsPressed()))
			{
				mouse.OnMouseMove(pt.x, pt.y);
			}
			else
			{
				ReleaseCapture();
				mouse.OnMouseLeave();
			}
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftReleased(pt.x, pt.y);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftPressed(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightReleased(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightPressed(pt.x, pt.y);
		break; 
	}
	//��껬��
	case WM_MOUSEWHEEL:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		mouse.OnWheelDelta(pt.x, pt.y, delta);
		break;
	}
	case WM_KEYDOWN:
		//���°���ʱ���ظ�����
		if (!(lParam & 0x40000000) || keyboard.AutorepeatIsEnable())
		{
			keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
		//ALT����VK_MEUN�˵�����ֻ����SYS KEY DOWN|UP  alt��������
	case WM_SYSKEYDOWN:
		if (!(lParam & 0x40000000) || keyboard.AutorepeatIsEnable())
		{
			keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_SYSKEYUP:
		keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
		break;
	case WM_KEYUP:
		keyboard.OnKeyRelease(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		keyboard.OnChar(static_cast<unsigned char>(wParam));
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Exception::Exception(int line, const char* file, HRESULT hrt) noexcept
	:MyException(line,file),
	hrt(hrt)
{}

const char* Window::Exception::What() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[�������]" << GetErrorCode() << std::endl
		<< "[��������]" << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	
	return whatBuffer.c_str();

}

const char* Window::Exception::GetType() const noexcept
{
	
	return "Ҫ��";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hrt) noexcept
{
	//���ָ�뽫ָ��FormatMessage�е�buffer
	char* pMsgBuf = nullptr;
	//���������ش����ַ����ĳ���
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		hrt,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0,nullptr
	);
	if (nMsgLen == 0) {
		return "δ֪����";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);//�ͷ�pMsgBuf
	return errorString;
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hrt;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hrt);
}

