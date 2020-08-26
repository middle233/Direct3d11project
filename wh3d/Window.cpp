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
	//任务栏图标
	wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));
	wc.hInstance = GetInstance();
	wc.hbrBackground = nullptr;
	wc.hCursor = nullptr;
	wc.lpszClassName = GetName();
	wc.lpszMenuName = nullptr;
	//标题栏图标
	wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());//注销一个窗口类
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
	//窗口创建函数
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	//异常：
	if (!(AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)))
	{
		throw MYWMD_LAST_EXCEPT();
	};
	//throw MYWMD_LAST_EXCEPT();
	//throw MYWMD_EXCEPT(ERROR_ARENA_TRASHED);
	//throw std::runtime_error("加油");
	//throw 12345656;
	hWnd = CreateWindow(
		WindowClass::GetName(),name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);
	//异常：没有创建窗口
	if (hWnd == nullptr) 
	{
		throw MYWMD_LAST_EXCEPT();
	}
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	pGfx = std::make_unique <Graphics>(hWnd);//这里用智能指针 代hWnd new了一个graphics
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
		//创建窗口成功发出消息（前面NC是带有用户栏的窗口）
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);//reinterpret_cast指针转换，把两个无关的类型转换，保留相同的比特位
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
		//窗口失去聚焦
	case WM_KILLFOCUS:
		keyboard.ClaerState();
		mouse.Flush();
		break;
		//鼠标移动
	case WM_MOUSEMOVE:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		//拖拽操作时，鼠标拖出了窗口外仍检测鼠标位置
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
			//在窗口外左/右键释放后Release掉鼠标捕获
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
	//鼠标滑轮
	case WM_MOUSEWHEEL:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		mouse.OnWheelDelta(pt.x, pt.y, delta);
		break;
	}
	case WM_KEYDOWN:
		//按下按键时不重复调用
		if (!(lParam & 0x40000000) || keyboard.AutorepeatIsEnable())
		{
			keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
		//ALT键是VK_MEUN菜单键，只有用SYS KEY DOWN|UP  alt键才能用
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
		<< "[错误代码]" << GetErrorCode() << std::endl
		<< "[错误描述]" << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	
	return whatBuffer.c_str();

}

const char* Window::Exception::GetType() const noexcept
{
	
	return "要得";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hrt) noexcept
{
	//这个指针将指向FormatMessage中的buffer
	char* pMsgBuf = nullptr;
	//函数将返回错误字符串的长度
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		hrt,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0,nullptr
	);
	if (nMsgLen == 0) {
		return "未知错误";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);//释放pMsgBuf
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

