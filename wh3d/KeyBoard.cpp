#include "KeyBoard.h"

bool KeyBoard::KeyIsPressed(unsigned char keycode) const noexcept
{
	return keystates[keycode];
}

KeyBoard::Event KeyBoard::ReadKey() noexcept
{
	if (keybuffer.size() > 0u)
	{
		//front()读取队列当前第一个按键事件
		KeyBoard::Event e = keybuffer.front();
		//pop()移除当前队列第一个事件
		keybuffer.pop();
		return e;
	}
	else
	{
		return KeyBoard::Event();
	}
	return Event();
}

bool KeyBoard::KeyIsEmpty() noexcept
{
	return keybuffer.empty();
}

void KeyBoard::FlushKey() noexcept
{
	keybuffer = std::queue<Event>();
}

char KeyBoard::ReadChar() noexcept
{
	if (charbuffer.size() > 0u)
	{
		unsigned char charcode = charbuffer.front();
		charbuffer.pop();
		return charcode;
	}
	else
	{
		return 0;
	}
	return 0;
}

bool KeyBoard::CharIsEmpty() noexcept
{
	return charbuffer.empty();
}

void KeyBoard::FlushChar() noexcept
{
	charbuffer = std::queue<char>();
}

void KeyBoard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}

void KeyBoard::EnableAutorepeat() noexcept
{
	autorepeatEnable = true;
}

void KeyBoard::DisableAutorepeat() noexcept
{
	autorepeatEnable = false;
}

bool KeyBoard::AutorepeatIsEnable() const noexcept
{
	return autorepeatEnable;
}

void KeyBoard::OnKeyPressed(unsigned char keycode) noexcept
{
	keystates[keycode] = true;
	keybuffer.push(KeyBoard::Event(KeyBoard::Event::Type::Press, keycode));
	
	TrimBuffer(keybuffer);
}

void KeyBoard::OnKeyRelease(unsigned char keycode) noexcept
{
	keystates[keycode] = false;
	keybuffer.push(KeyBoard::Event(KeyBoard::Event::Type::release, keycode));
	TrimBuffer(keybuffer);
}

void KeyBoard::OnChar(char character) noexcept
{
	charbuffer.push(character);
	TrimBuffer(charbuffer);
}

void KeyBoard::ClaerState() noexcept
{
	keystates.reset();
}
template<typename T>
void KeyBoard::TrimBuffer(std::queue<T>& buffer)noexcept
{
	while (buffer.size()>bufferSize)
	{
		buffer.pop();
	}
}