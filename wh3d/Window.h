#pragma once
#include"MyWin.h"
#include"Graphics.h"
#include<memory>
#include"MyException.h"
#include"KeyBoard.h"
#include"Mouse.h"
#include<optional>

class Window
{
public:
	/// <summary>
	/// 异常弹出窗口
	/// </summary>
	class Exception :public MyException
	{
	public:
		//构造异常窗口时，hrt表示window的HRESULE错误代码
		Exception(int line, const char* file, HRESULT hrt)noexcept ;
		virtual const char* What()const noexcept ;
		virtual const char* GetType() const noexcept;
		//用string描述hrt错误代码，让人能看懂
		static std::string TranslateErrorCode(HRESULT hrt)noexcept;
		//获取hrt错误代码
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString()const noexcept;
	private:
		HRESULT hrt;
		
	};

	
private:
	/// <summary>
	/// 单例窗口
	/// </summary>
	class WindowClass
	{
	public:
		//获取窗口名称（LPCWSTR格式的字符串）
		static const char* GetName() noexcept;
		//获取单例
		static HINSTANCE GetInstance() noexcept;
	private:
		//私有构造函数，单例
		WindowClass() noexcept;
		//释放单例
		~WindowClass();
		WindowClass(const WindowClass&) = delete;//=delete意思是让这个函数不会被调用，单例常见操作
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName ="My Direct3D Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
	
public:
	//创建包含窗口类
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetTile(const std::string);
	static std::optional<int> ProcessMessages();
	Graphics& Gfx();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hwnd, UINT msg, WPARAM wPARAM, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hwnd, UINT msg, WPARAM wPARAM, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	KeyBoard keyboard;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};
//助手宏让你的异常，更加丝滑，__LINE__就是获取当前行数file同理
#define MYWMD_EXCEPT(hrt) Window::Exception(__LINE__,__FILE__,hrt)
#define MYWMD_LAST_EXCEPT() Window::Exception(__LINE__,__FILE__,GetLastError())
