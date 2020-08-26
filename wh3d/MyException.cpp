#include "MyException.h"
#include <sstream>
MyException::MyException(int line, const char* file) noexcept
	:
	line(line),//这是直接在构造函数中声明了行数和文件
	file(file)
{}

const char* MyException::What() const noexcept//指向内存的
{
	std::ostringstream oss;//oss在函数结束消失，直接指向oss指针将出错
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();//所以建立的字符缓存区，把oss存到WhatBuffer中
	return whatBuffer.c_str();
}
const char* MyException::GetType() const noexcept {
	return "MyException";
}
int MyException::GetLine() const noexcept
{
	return line;
}
const std::string& MyException::GetFile() const noexcept
{
	return file;
}
std::string MyException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File]" << file << std::endl
		<< "[Line]" << line;
	return oss.str();

}