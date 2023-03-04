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
		GameEngineInput::CreateKey("TitleSelect", 'Z');
	}

	// Player Action == ����Ű, ESC, Z, X, C, A, S
	if (false == GameEngineInput::IsKey("PlayerMove"))            // �÷��̾ ���
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
		GameEngineInput::CreateKey("NextLevel", 'P');         // ���� ������ �̵�(�� ����)
		GameEngineInput::CreateKey("BeforeLevel", 'O');       // ���� ������ �̵�(�� ����)
		GameEngineInput::CreateKey("FreeMoveOn", '1');        // �������� on (�÷��̾�)
		GameEngineInput::CreateKey("FreeMoveOff", '2');       // �������� off (�÷��̾�)
		GameEngineInput::CreateKey("ColMapSwitch", '3');      // ColMapRender (�� ����)
		GameEngineInput::CreateKey("PositionText", '4');      // ��ġ �ؽ�Ʈ (�÷��̾�)
		GameEngineInput::CreateKey("DebugRenderSwitch", '5'); // �浹ü, �ؽ�Ʈ�ڽ� (�÷��̾�)
		GameEngineInput::CreateKey("MonsterTest", 'Q');       // ���� �׽�Ʈ (�÷��̾� or ����)
		GameEngineInput::CreateKey("CreateMonster", 'W');     // ���̸��� ���� (�÷��̾�)
		GameEngineInput::CreateKey("CreateItem", 'E');		  // ���̾����� ���� (�÷��̾�)
		GameEngineInput::CreateKey("HPPlus", 'R');		      // �÷��̾� ü�� ���� (�÷��̾�)
		GameEngineInput::CreateKey("HPMinus", 'T');		      // �÷��̾� ü�� ���� (�÷��̾�)
		GameEngineInput::CreateKey("Showmethemoney", 'Y');	  // �÷��̾� �� 900 (�÷��̾�)
	}
}