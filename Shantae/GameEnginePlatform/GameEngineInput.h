#pragma once

#include <map>
#include <string>
#include <Windows.h>

class GameEngineWindow;

// 설명 :
class GameEngineInput
{
	friend GameEngineWindow; // AnyKey

private: // 외부에서 활용할 수 없도록 private
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down  = false;    // 누른 순간
		bool Up    = false;    // 땐 순간
		bool Press = false;    // 입력
		bool Free  = true;     // 입력 안함

		float PressTime = 0.0; // 키를 누른 시간
		int Key = -1;

		// 이전 프레임 체크
		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key);
		}

		// 이전 프레임에 대한 키입력값 확인
		void Update(float _DeltaTime);
	};

public:
	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

	// 할당한 키들의 상태 확인
	static void Update(float _DeltaTime);

	// 새로운 키 할당
	static void CreateKey(const std::string_view& _Name, int _Key);

	// 해당 키가 존재하는지?
	static bool IsKey(const std::string_view& _Name);

	// 할당한 키들의 현재 상태
	static bool IsDown(const std::string_view& _Name);
	static bool IsUp(const std::string_view& _Name);
	static bool IsPress(const std::string_view& _Name);
	static bool IsFree(const std::string_view& _Name);

	// 키가 눌렸던 시간 리턴
	static float GetPressTime(const std::string_view& _Name);

	// 마우스 커서 감추기
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

	// 키값 저장
	static std::map<std::string, GameEngineKey> Keys;

	// 아무키나 눌러도 인식(Window 매크로 함수와 연결)
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


