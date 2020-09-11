#include "Surface.h"

Surface::Surface(unsigned int width, unsigned int height, unsigned int pitch)
	:width(width),
	height(height)
{}

Surface::Surface(unsigned int width, unsigned int height)
	: width(width),
	height(height)
{}

Surface::Surface(Surface&& source)
	:pBuffer(std::move(source.pBuffer)),
	width(source.width),
	height(source.height)
{}

Surface::~Surface()
{
}

void Surface::Clear(Color fillValue)
{
}

void Surface::PutPixel(unsigned int x, unsigned int y, Color c)
	:
{
}

Surface::Color Surface::GetPixel(unsigned int x, unsigned int y) const
{
	return Color();
}

unsigned int Surface::GetWidth() const
{
	return 0;
}

unsigned int Surface::GetHeight() const
{
	return 0;
}

Surface::Color* Surface::GetBufferPtr()
{
	return nullptr;
}

const Surface::Color* Surface::GetBufferPtr() const
{
	return nullptr;
}

const Surface::Color* Surface::GetBufferPtrConst() const
{
	return nullptr;
}

Surface Surface::FromFile(const std::string& name)
{
	return Surface();
}

void Surface::Save(const std::string& filename) const
{
}

void Surface::Copy(const Surface& src)
{
}
