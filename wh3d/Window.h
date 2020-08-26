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
	/// �쳣��������
	/// </summary>
	class Exception :public MyException
	{
	public:
		//�����쳣����ʱ��hrt��ʾwindow��HRESULE�������
		Exception(int line, const char* file, HRESULT hrt)noexcept ;
		virtual const char* What()const noexcept ;
		virtual const char* GetType() const noexcept;
		//��string����hrt������룬�����ܿ���
		static std::string TranslateErrorCode(HRESULT hrt)noexcept;
		//��ȡhrt�������
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString()const noexcept;
	private:
		HRESULT hrt;
		
	};

	
private:
	/// <summary>
	/// ��������
	/// </summary>
	class WindowClass
	{
	public:
		//��ȡ�������ƣ�LPCWSTR��ʽ���ַ�����
		static const char* GetName() noexcept;
		//��ȡ����
		static HINSTANCE GetInstance() noexcept;
	private:
		//˽�й��캯��������
		WindowClass() noexcept;
		//�ͷŵ���
		~WindowClass();
		WindowClass(const WindowClass&) = delete;//=delete��˼��������������ᱻ���ã�������������
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName ="My Direct3D Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
	
public:
	//��������������
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
//���ֺ�������쳣������˿����__LINE__���ǻ�ȡ��ǰ����fileͬ��
#define MYWMD_EXCEPT(hrt) Window::Exception(__LINE__,__FILE__,hrt)
#define MYWMD_LAST_EXCEPT() Window::Exception(__LINE__,__FILE__,GetLastError())
