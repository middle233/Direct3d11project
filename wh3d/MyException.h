#pragma once
#include<string>
#include<exception>
#include"MyWin.h"
class MyException: public std::exception
{
public:
	MyException(int line, const char* file)noexcept;
	//ʲô�쳣������What��const���͵ģ�������޸ģ���Ҫ����������mutable
	virtual const char* What() const noexcept ;
	//�쳣Type
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;
private:
	int line;
	std::string file;//�ܻ�������쳣���쳣�������쳣��Ϣ
protected:
	//�쳣������-һ��mutble��string,LPCWSTR
	mutable std::string whatBuffer;
	mutable std::string tpyeBuffer;
};

