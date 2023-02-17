#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include "GameEngineInput.h"

std::map<std::string, GameEngineInput::GameEngineKey> GameEngineInput::Keys;
bool GameEngineInput::IsAnyKeyValue = false;

GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
}

// 이전 프레임에 대한 키입력값 확인
void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	// 이전 프레임에 입력이 있었다.
	if (true == KeyCheck())
	{
		PressTime += _DeltaTime;

		// 하지만 지금은 입력 안함
		if (true == Free)
		{
			Down = true;    // 누른 순간
			Up = false;	  	// 땐 순간
			Press = true; 	// 입력
			Free = false; 	// 입력 안함
		}
		// 지금도 입력중
		else if (true == Down)
		{
			Down = false;   // 누른 순간
			Up = false;	  	// 땐 순간
			Press = true; 	// 입력
			Free = false; 	// 입력 안함
		}
	}
	// 이전 프레임에 입력이 없었다.
	else
	{
		PressTime = 0.0f;

		// 지금부터 새로 입력
		if (true == Press)
		{
			Down = false;   // 누른 순간
			Up = true;		// 땐 순간
			Press = false;	// 입력
			Free = true;	// 입력 안함
		}
		// 지금도 입력 안함
		else if (true == Up)
		{
			Down = false;   // 누른 순간
			Up = false;		// 땐 순간
			Press = false;	// 입력
			Free = true;	// 입력 안함
		}
	}
}

// 할당한 키들의 상태 확인
void GameEngineInput::Update(float _DeltaTime)
{
	std::map<std::string, GameEngineKey>::iterator StartKeyIter = Keys.begin();
	std::map<std::string, GameEngineKey>::iterator EndKeyIter = Keys.end();

	for (; StartKeyIter != EndKeyIter; ++StartKeyIter)
	{
		StartKeyIter->second.Update(_DeltaTime);
	}
}

// 새로운 키 할당
void GameEngineInput::CreateKey(const std::string_view& _Name, int _Key)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() != Keys.find(UpperName))
	{
		MsgAssert("이미 존재하는 이름의 키를 또 만들려고 했습니다.");
	}

	_Key = toupper(_Key);

	Keys[UpperName].Key = _Key;
}

// 해당 키가 존재하는지?
bool GameEngineInput::IsKey(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	return Keys.end() != Keys.find(UpperName);
}

// 할당한 키들의 현재 상태(Down)
bool GameEngineInput::IsDown(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	return Keys[UpperName].Down;
}

// 할당한 키들의 현재 상태(Up)
bool GameEngineInput::IsUp(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	return Keys[UpperName].Up;
}

// 할당한 키들의 현재 상태(Press)
bool GameEngineInput::IsPress(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	return Keys[UpperName].Press;
}

// 할당한 키들의 현재 상태(Free)
bool GameEngineInput::IsFree(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	return Keys[UpperName].Free;
}

// 키가 눌렸던 시간 리턴
float GameEngineInput::GetPressTime(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	return Keys[UpperName].PressTime;
}

void GameEngineInput::MouseCursorOff()
{
	// Windows 함수, 윈도우 창 내 마우스 커서를 감춘다.
	ShowCursor(FALSE);
}