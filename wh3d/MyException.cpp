#include "MyException.h"
#include <sstream>
MyException::MyException(int line, const char* file) noexcept
	:
	line(line),//����ֱ���ڹ��캯�����������������ļ�
	file(file)
{}

const char* MyException::What() const noexcept//ָ���ڴ��
{
	std::ostringstream oss;//oss�ں���������ʧ��ֱ��ָ��ossָ�뽫����
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();//���Խ������ַ�����������oss�浽WhatBuffer��
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