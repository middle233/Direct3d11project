#pragma once
#include"MyWin.h"
#include<string>
#include<memory>
class Surface
{
public:
public:
	class Color
	{
	public:
		//һ����������ÿ8λ����һ��255��ɫ������һ�������д���XRBG�ĸ�ֵ
		unsigned int dword;
	public:
		constexpr Color() noexcept : dword()
		{
		}
		//ת�ƹ���
		constexpr Color(const Color& col) noexcept
			:
			dword(col.dword)
		{
		}
		constexpr Color(unsigned int dw) noexcept
			:
			dword(dw)
		{
		}
		constexpr Color(unsigned char x, unsigned char r, unsigned char g, unsigned char b) noexcept
			:
			dword((x << 24u) | (r << 16u) | (g << 8u) | b)
		{
		}
		constexpr Color(unsigned char r, unsigned char g, unsigned char b) noexcept
			:
			dword((r << 16u) | (g << 8u) | b)
		{
		}
		constexpr Color(Color col, unsigned char x) noexcept
			:
			Color((x << 24u) | col.dword)
		{
		}

		Color& operator =(Color color) noexcept
		{
			dword = color.dword;
			return *this;
		}

		constexpr unsigned char GetX() const noexcept
		{
			return dword >> 24u;
		}
		constexpr unsigned char GetA() const noexcept
		{
			return GetX();
		}
		constexpr unsigned char GetR() const noexcept
		{
			return (dword >> 16u) & 0xFFu;
		}
		constexpr unsigned char GetG() const noexcept
		{
			return (dword >> 8u) & 0xFFu;
		}
		constexpr unsigned char GetB() const noexcept
		{
			return dword & 0xFFu;
		}

		void SetX(unsigned char x) noexcept
		{
			dword = (dword & 0xFFFFFFu) | (x << 24u);
		}
		void SetA(unsigned char a) noexcept
		{
			SetX(a);
		}
		void SetR(unsigned char r) noexcept
		{
			dword = (dword & 0xFF00FFFFu) | (r << 16u);
		}
		void SetG(unsigned char g) noexcept
		{
			dword = (dword & 0xFFFF00FFu) | (g << 8u);
		}
		void SetB(unsigned char b) noexcept
		{
			dword = (dword & 0xFFFFFF00u) | b;
		}
	};
public:
	Surface(unsigned int width, unsigned int height, unsigned int pitch);
	Surface(unsigned int width, unsigned int height);
	Surface(Surface&& source);
	Surface(Surface&) = delete;
	Surface& operator=(Surface&& donor) ;
	Surface& operator=(const Surface&) = delete;
	~Surface();

	void Clear(Color fillValue);
	void PutPixel(unsigned int x, unsigned int y, Color c);
	Color GetPixel(unsigned int x, unsigned int y) const;
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	Color* GetBufferPtr();
	const Color* GetBufferPtr() const;
	const Color* GetBufferPtrConst() const;
	static Surface FromFile(const std::string& name);
	void Save(const std::string& filename)const;
	void Copy(const Surface& src);
private:
	Surface(unsigned int width, unsigned int height, std::unique_ptr<Color[]> pBufferPixel);
private:
	std::unique_ptr<Color[]> pBuffer;
	unsigned int width;
	unsigned int height;
};

