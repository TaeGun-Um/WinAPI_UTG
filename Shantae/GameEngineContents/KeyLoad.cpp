#include "KeyLoad.h"

#include <GameEnginePlatform/GameEngineInput.h>

KeyLoad::KeyLoad() 
{
}

KeyLoad::~KeyLoad() 
{
}

void KeyLoad::Loading()
{
	// 0130, 0201
	if (false == GameEngineInput::IsKey("TitleScroll"))
	{
		GameEngineInput::CreateKey("TitleScrollLeft", 'A');
		GameEngineInput::CreateKey("TitleScrollRight", 'D');
		GameEngineInput::CreateKey("TitleScrollUp", 'W');
		GameEngineInput::CreateKey("TitleScrollDown", 'S');
	}

	// Title
	if (false == GameEngineInput::IsKey("SelectMoveRight"))
	{
		GameEngineInput::CreateKey("SelectMoveRight", VK_RIGHT);
	}
	if (false == GameEngineInput::IsKey("SelectMoveLeft"))
	{
		GameEngineInput::CreateKey("SelectMoveLeft", VK_LEFT);
	}
	if (false == GameEngineInput::IsKey("Select"))
	{
		GameEngineInput::CreateKey("Select", 'Z');
	}

	// Player Action
	if (false == GameEngineInput::IsKey("UpMove"))
	{
		GameEngineInput::CreateKey("UpMove", VK_UP);
	}
	if (false == GameEngineInput::IsKey("DownMove"))
	{
		GameEngineInput::CreateKey("DownMove", VK_DOWN);
	}
	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", VK_LEFT);
	}
	if (false == GameEngineInput::IsKey("RightMove"))
	{
		GameEngineInput::CreateKey("RightMove", VK_RIGHT);
	}
	if (false == GameEngineInput::IsKey("Attack"))
	{
		GameEngineInput::CreateKey("Attack", 'Z');
	}
	if (false == GameEngineInput::IsKey("Jump"))
	{
		GameEngineInput::CreateKey("Jump", 'X');
	}
	if (false == GameEngineInput::IsKey("Fire"))
	{
		GameEngineInput::CreateKey("Fire", 'C');
	}
	if (false == GameEngineInput::IsKey("Back"))
	{
		GameEngineInput::CreateKey("Back", '\x1b');
	}

	// µð¹ö±ë¿ë Å°
	if (false == GameEngineInput::IsKey("NextLevel"))
	{
		GameEngineInput::CreateKey("NextLevel", 'P');
	}
	if (false == GameEngineInput::IsKey("BeforeLevel"))
	{
		GameEngineInput::CreateKey("BeforeLevel", 'O');
	}
	if (false == GameEngineInput::IsKey("FreeMoveOn"))
	{
		GameEngineInput::CreateKey("FreeMoveOn", '1');
	}
	if (false == GameEngineInput::IsKey("FreeMoveOff"))
	{
		GameEngineInput::CreateKey("FreeMoveOff", '2');
	}
	if (false == GameEngineInput::IsKey("ColMapSwitch"))
	{
		GameEngineInput::CreateKey("ColMapSwitch", '3');
	}
	if (false == GameEngineInput::IsKey("PositionText"))
	{
		GameEngineInput::CreateKey("PositionText", '4');
	}
	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", '5');
	}
	if (false == GameEngineInput::IsKey("MonsterTest"))
	{
		GameEngineInput::CreateKey("MonsterTest", 'A');
	}
	if (false == GameEngineInput::IsKey("CreateMonster"))
	{
		GameEngineInput::CreateKey("CreateMonster", 'S');
	}
}