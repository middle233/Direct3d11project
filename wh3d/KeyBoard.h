#pragma once
#include<queue>
#include<bitset>

class KeyBoard
{
	friend class Window;
public:
	//声明事件
	class Event 
	{
	public:
		enum class Type
		{
			//按下
			Press,
			//松开
			release,
			//无效
			Invalid
		};
	private:
		Type type;
		unsigned char code;
	public:

		Event():type(Type::Invalid),code(0u){}

		Event(Type type ,unsigned char code) noexcept
			:
			type(type),
			code(code)
		{}
		bool IsPress() const noexcept
		{
			return type == Type::Press;

		}
		bool IsRelease() const noexcept
		{
			return type == Type::release;
		}
		unsigned char GetCode() const noexcept
		{
			return code;
		}
	};
public:
	//= default就是默认构造函数

	KeyBoard() = default;
	KeyBoard(const KeyBoard&) = delete;
	KeyBoard& operator=(const KeyBoard&) = delete;

	//key Event事件 

	bool KeyIsPressed(unsigned char keycode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() noexcept;
	//清除刷新队列
	void FlushKey() noexcept;

	//char Event事件

	char ReadChar() noexcept;
	bool CharIsEmpty() noexcept;
	void FlushChar() noexcept;
	void Flush() noexcept;

	//autorepeat control 自动重复按键控制 按下一个建不动时，不断的发送按下指令

	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool AutorepeatIsEnable() const noexcept;
private:
	void OnKeyPressed(unsigned char keycode) noexcept;
	void OnKeyRelease(unsigned char keycode) noexcept;
	void OnChar(char character) noexcept;
	void ClaerState() noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer) noexcept;
private:
	static constexpr unsigned int nKey = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnable = false;
	//类似数组，但其中的元素只能是1和0，keystates中存储的是按键的状态，按下是1松开是0
	std::bitset<nKey> keystates;
	//按键事件队列缓冲区
	std::queue<Event> keybuffer;
	std::queue<char> charbuffer;
};
//buffer.size超过成员bufferSize后会pop掉第一个

