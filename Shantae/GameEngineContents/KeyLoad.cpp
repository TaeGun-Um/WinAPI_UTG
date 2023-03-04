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
	// Title
	if (false == GameEngineInput::IsKey("TitleActorMove"))        // 타이틀화면에서만 사용
	{
		GameEngineInput::CreateKey("SelectMoveRight", VK_RIGHT);
		GameEngineInput::CreateKey("SelectMoveLeft", VK_LEFT);
		GameEngineInput::CreateKey("TitleSelect", 'Z');
	}

	// Player Action == 방향키, ESC, Z, X, C, A, S
	if (false == GameEngineInput::IsKey("PlayerMove"))            // 플레이어만 사용
	{
		GameEngineInput::CreateKey("UpMove", VK_UP);
		GameEngineInput::CreateKey("DownMove", VK_DOWN);
		GameEngineInput::CreateKey("LeftMove", VK_LEFT);
		GameEngineInput::CreateKey("RightMove", VK_RIGHT);
		GameEngineInput::CreateKey("Attack", 'Z');
		GameEngineInput::CreateKey("Jump", 'X');
		GameEngineInput::CreateKey("Fire", 'C');
		GameEngineInput::CreateKey("Select", 'A');
		GameEngineInput::CreateKey("Inventory", 'S');
		GameEngineInput::CreateKey("TextTest", 'D');
		GameEngineInput::CreateKey("Back", '\x1b');
	}

	// Debug == P, O, A, S, 1, 2, 3, 4, 5
	if (false == GameEngineInput::IsKey("Debug"))    
	{
		GameEngineInput::CreateKey("NextLevel", 'P');         // 다음 레벨로 이동(각 레벨)
		GameEngineInput::CreateKey("BeforeLevel", 'O');       // 이전 레벨로 이동(각 레벨)
		GameEngineInput::CreateKey("FreeMoveOn", '1');        // 프리무브 on (플레이어)
		GameEngineInput::CreateKey("FreeMoveOff", '2');       // 프리무브 off (플레이어)
		GameEngineInput::CreateKey("ColMapSwitch", '3');      // ColMapRender (각 레벨)
		GameEngineInput::CreateKey("PositionText", '4');      // 위치 텍스트 (플레이어)
		GameEngineInput::CreateKey("DebugRenderSwitch", '5'); // 충돌체, 텍스트박스 (플레이어)
		GameEngineInput::CreateKey("MonsterTest", 'Q');       // 몬스터 테스트 (플레이어 or 몬스터)
		GameEngineInput::CreateKey("CreateMonster", 'W');     // 더미몬스터 생성 (플레이어)
		GameEngineInput::CreateKey("CreateItem", 'E');		  // 더미아이템 생성 (플레이어)
		GameEngineInput::CreateKey("HPPlus", 'R');		      // 플레이어 체력 증가 (플레이어)
		GameEngineInput::CreateKey("HPMinus", 'T');		      // 플레이어 체력 감소 (플레이어)
		GameEngineInput::CreateKey("Showmethemoney", 'Y');	  // 플레이어 돈 900 (플레이어)
	}
}