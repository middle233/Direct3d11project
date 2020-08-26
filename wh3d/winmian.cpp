
#include"App.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     IpCmdLine,
	int       nCmdShow) 
{
	try
	{
		return App{}.Go();
	}
	catch (const MyException & me)
	{
		MessageBox
		(
			//这里可以放窗口的句柄，指在这个“MesageBox”消失前，无法操作的母窗口
			nullptr,
			me.what(),
			me.GetType(), MB_OK | MB_ICONEXCLAMATION
		);
	}
	catch (const std::exception & me)
	{
		MessageBox(nullptr, me.what(), "标准错误", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "无详细信息", "未知错误", MB_OK | MB_ICONEXCLAMATION);
	}


	return -1;
	
}