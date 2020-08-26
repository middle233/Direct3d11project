
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
			//������ԷŴ��ڵľ����ָ�������MesageBox����ʧǰ���޷�������ĸ����
			nullptr,
			me.what(),
			me.GetType(), MB_OK | MB_ICONEXCLAMATION
		);
	}
	catch (const std::exception & me)
	{
		MessageBox(nullptr, me.what(), "��׼����", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "����ϸ��Ϣ", "δ֪����", MB_OK | MB_ICONEXCLAMATION);
	}


	return -1;
	
}