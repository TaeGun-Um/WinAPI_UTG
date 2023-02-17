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

// ���� �����ӿ� ���� Ű�Է°� Ȯ��
void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	// ���� �����ӿ� �Է��� �־���.
	if (true == KeyCheck())
	{
		PressTime += _DeltaTime;

		// ������ ������ �Է� ����
		if (true == Free)
		{
			Down = true;    // ���� ����
			Up = false;	  	// �� ����
			Press = true; 	// �Է�
			Free = false; 	// �Է� ����
		}
		// ���ݵ� �Է���
		else if (true == Down)
		{
			Down = false;   // ���� ����
			Up = false;	  	// �� ����
			Press = true; 	// �Է�
			Free = false; 	// �Է� ����
		}
	}
	// ���� �����ӿ� �Է��� ������.
	else
	{
		PressTime = 0.0f;

		// ���ݺ��� ���� �Է�
		if (true == Press)
		{
			Down = false;   // ���� ����
			Up = true;		// �� ����
			Press = false;	// �Է�
			Free = true;	// �Է� ����
		}
		// ���ݵ� �Է� ����
		else if (true == Up)
		{
			Down = false;   // ���� ����
			Up = false;		// �� ����
			Press = false;	// �Է�
			Free = true;	// �Է� ����
		}
	}
}

// �Ҵ��� Ű���� ���� Ȯ��
void GameEngineInput::Update(float _DeltaTime)
{
	std::map<std::string, GameEngineKey>::iterator StartKeyIter = Keys.begin();
	std::map<std::string, GameEngineKey>::iterator EndKeyIter = Keys.end();

	for (; StartKeyIter != EndKeyIter; ++StartKeyIter)
	{
		StartKeyIter->second.Update(_DeltaTime);
	}
}

// ���ο� Ű �Ҵ�
void GameEngineInput::CreateKey(const std::string_view& _Name, int _Key)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() != Keys.find(UpperName))
	{
		MsgAssert("�̹� �����ϴ� �̸��� Ű�� �� ������� �߽��ϴ�.");
	}

	_Key = toupper(_Key);

	Keys[UpperName].Key = _Key;
}

// �ش� Ű�� �����ϴ���?
bool GameEngineInput::IsKey(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	return Keys.end() != Keys.find(UpperName);
}

// �Ҵ��� Ű���� ���� ����(Down)
bool GameEngineInput::IsDown(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
	}

	return Keys[UpperName].Down;
}

// �Ҵ��� Ű���� ���� ����(Up)
bool GameEngineInput::IsUp(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
	}

	return Keys[UpperName].Up;
}

// �Ҵ��� Ű���� ���� ����(Press)
bool GameEngineInput::IsPress(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
	}

	return Keys[UpperName].Press;
}

// �Ҵ��� Ű���� ���� ����(Free)
bool GameEngineInput::IsFree(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
	}

	return Keys[UpperName].Free;
}

// Ű�� ���ȴ� �ð� ����
float GameEngineInput::GetPressTime(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
	}

	return Keys[UpperName].PressTime;
}

void GameEngineInput::MouseCursorOff()
{
	// Windows �Լ�, ������ â �� ���콺 Ŀ���� �����.
	ShowCursor(FALSE);
}