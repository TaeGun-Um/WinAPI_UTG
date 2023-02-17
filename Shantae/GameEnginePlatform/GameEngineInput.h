#pragma once

#include <map>
#include <string>
#include <Windows.h>

class GameEngineWindow;

// ���� :
class GameEngineInput
{
	friend GameEngineWindow; // AnyKey

private: // �ܺο��� Ȱ���� �� ������ private
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down  = false;    // ���� ����
		bool Up    = false;    // �� ����
		bool Press = false;    // �Է�
		bool Free  = true;     // �Է� ����

		float PressTime = 0.0; // Ű�� ���� �ð�
		int Key = -1;

		// ���� ������ üũ
		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key);
		}

		// ���� �����ӿ� ���� Ű�Է°� Ȯ��
		void Update(float _DeltaTime);
	};

public:
	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

	// �Ҵ��� Ű���� ���� Ȯ��
	static void Update(float _DeltaTime);

	// ���ο� Ű �Ҵ�
	static void CreateKey(const std::string_view& _Name, int _Key);

	// �ش� Ű�� �����ϴ���?
	static bool IsKey(const std::string_view& _Name);

	// �Ҵ��� Ű���� ���� ����
	static bool IsDown(const std::string_view& _Name);
	static bool IsUp(const std::string_view& _Name);
	static bool IsPress(const std::string_view& _Name);
	static bool IsFree(const std::string_view& _Name);

	// Ű�� ���ȴ� �ð� ����
	static float GetPressTime(const std::string_view& _Name);

	// ���콺 Ŀ�� ���߱�
	static void MouseCursorOff();

	// AnyKey
	static bool IsAnyKey()
	{
		return IsAnyKeyValue;
	}

protected:

private:
	GameEngineInput();
	~GameEngineInput();

	// Ű�� ����
	static std::map<std::string, GameEngineKey> Keys;

	// �ƹ�Ű�� ������ �ν�(Window ��ũ�� �Լ��� ����)
	static bool IsAnyKeyValue;

	static void IsAnyKeyOn()
	{
		IsAnyKeyValue = true;
	}

	static void IsAnyKeyOff()
	{
		IsAnyKeyValue = false;
	}
};


