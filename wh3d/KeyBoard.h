#pragma once
#include<queue>
#include<bitset>

class KeyBoard
{
	friend class Window;
public:
	//�����¼�
	class Event 
	{
	public:
		enum class Type
		{
			//����
			Press,
			//�ɿ�
			release,
			//��Ч
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
	//= default����Ĭ�Ϲ��캯��

	KeyBoard() = default;
	KeyBoard(const KeyBoard&) = delete;
	KeyBoard& operator=(const KeyBoard&) = delete;

	//key Event�¼� 

	bool KeyIsPressed(unsigned char keycode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() noexcept;
	//���ˢ�¶���
	void FlushKey() noexcept;

	//char Event�¼�

	char ReadChar() noexcept;
	bool CharIsEmpty() noexcept;
	void FlushChar() noexcept;
	void Flush() noexcept;

	//autorepeat control �Զ��ظ��������� ����һ��������ʱ�����ϵķ��Ͱ���ָ��

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
	//�������飬�����е�Ԫ��ֻ����1��0��keystates�д洢���ǰ�����״̬��������1�ɿ���0
	std::bitset<nKey> keystates;
	//�����¼����л�����
	std::queue<Event> keybuffer;
	std::queue<char> charbuffer;
};
//buffer.size������ԱbufferSize���pop����һ��

