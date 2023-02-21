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
	if (false == GameEngineInput::IsKey("TitleActorMove"))        // Ÿ��Ʋȭ�鿡���� ���
	{
		GameEngineInput::CreateKey("SelectMoveRight", VK_RIGHT);
		GameEngineInput::CreateKey("SelectMoveLeft", VK_LEFT);
		GameEngineInput::CreateKey("Select", 'Z');

		// �������� �׽�Ʈ��
		GameEngineInput::CreateKey("TitleScrollLeft", 'A');
		GameEngineInput::CreateKey("TitleScrollRight", 'D');
		GameEngineInput::CreateKey("TitleScrollUp", 'W');
		GameEngineInput::CreateKey("TitleScrollDown", 'S');
	}

	// Player Action == ����Ű, ESC, Z, X, C
	if (false == GameEngineInput::IsKey("PlayerMove"))            // �÷��̾ ���
	{
		GameEngineInput::CreateKey("UpMove", VK_UP);
		GameEngineInput::CreateKey("DownMove", VK_DOWN);
		GameEngineInput::CreateKey("LeftMove", VK_LEFT);
		GameEngineInput::CreateKey("RightMove", VK_RIGHT);
		GameEngineInput::CreateKey("Attack", 'Z');
		GameEngineInput::CreateKey("Jump", 'X');
		GameEngineInput::CreateKey("Fire", 'C');
		GameEngineInput::CreateKey("Back", '\x1b');
	}

	// Debug == P, O, A, S, 1, 2, 3, 4, 5
	if (false == GameEngineInput::IsKey("Debug"))    
	{
		GameEngineInput::CreateKey("NextLevel", 'P');         // ���� ������ �̵�(�� ����)
		GameEngineInput::CreateKey("BeforeLevel", 'O');       // ���� ������ �̵�(�� ����)
		GameEngineInput::CreateKey("FreeMoveOn", '1');        // �������� on (�÷��̾�)
		GameEngineInput::CreateKey("FreeMoveOff", '2');       // �������� off (�÷��̾�)
		GameEngineInput::CreateKey("ColMapSwitch", '3');      // ColMapRender (�� ����)
		GameEngineInput::CreateKey("PositionText", '4');      // ��ġ �ؽ�Ʈ (�÷��̾�)
		GameEngineInput::CreateKey("DebugRenderSwitch", '5'); // �浹ü, �ؽ�Ʈ�ڽ� (�÷��̾�)
		GameEngineInput::CreateKey("MonsterTest", 'A');       // ���� �׽�Ʈ (�÷��̾� or ����)
		GameEngineInput::CreateKey("CreateMonster", 'S');     // ���̸��� ���� (�÷��̾�)
	}
}