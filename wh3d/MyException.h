#pragma once
#include<string>
#include<exception>
#include"MyWin.h"
class MyException: public std::exception
{
public:
	MyException(int line, const char* file)noexcept;
	//什么异常，这里What是const类型的，如进行修改，需要在其中声明mutable
	virtual const char* What() const noexcept ;
	//异常Type
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;
private:
	int line;
	std::string file;//能获得两种异常，异常行数，异常信息
protected:
	//异常缓冲区-一个mutble的string,LPCWSTR
	mutable std::string whatBuffer;
	mutable std::string tpyeBuffer;
};

