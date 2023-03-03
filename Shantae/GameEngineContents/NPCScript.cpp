#include "NPCScript.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "BlueTextBox.h"
#include "Player.h"

NPCScript::NPCScript() 
{
}

NPCScript::~NPCScript() 
{
}

void NPCScript::Start()
{
	TextRender = CreateRender(RenderOrder::UI);
	Script = "��������������������������������������������\n��������������������������������������������";
	BoxScale = { 650, 300 };
	TextRender->SetText(Script, 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	TextRender->EffectCameraOff();
}

void NPCScript::Update(float _DeltaTime)
{
	if (1 == TextCount)
	{
		TextCount = 0;
		NPCType();
	}

	TextCreate();
}

void NPCScript::TextCreate()
{
	if (TextnNextCount - TextInsertCount == TextInsertCount)
	{
		IsTextEnd = true;
	}

	if (true == IsTextEnd)
	{
		BlueTextBox::DialogTextBox->SetIsOver();
	}
	else if (false == IsTextEnd)
	{
		TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	}
}

void NPCScript::NPCType()
{
	switch (NPCValue)
	{
	case NPCDialogType_Dialog::Sky:
		Script = "Sky";
		TextInsertCount = 5;
		Sky();
		break;
	case NPCDialogType_Dialog::Bathwoman:
		Script = "Bathwoman";
		TextInsertCount = 1;
		Bathwoman();
		break;
	case NPCDialogType_Dialog::Merchant:
		Script = "Merchant";
		TextInsertCount = 24;
		Merchant();
		break;
	case NPCDialogType_Dialog::Squidsmith:
		Script = "Squidsmith";
		TextInsertCount = 11;
		Squidsmith();
		break;
	case NPCDialogType_Dialog::Town_Guard:
		Script = "Town_Guard";
		TextInsertCount = 1;
		TownGuard();
		break;
	case NPCDialogType_Dialog::Town_Guard_Pass:
		Script = "Town_Guard_Pass";
		TextInsertCount = 6;
		TownGuard_Pass();
		break;
	default:
		break;
	}
}

void NPCScript::Kill()
{
	GameEngineActor* ColActor = TextRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}

void NPCScript::TownGuard()
{
	NPCTexts.resize(TextInsertCount);
	NPCTexts[0] = "���⼭���ʹ� ��ĿƲ �����̾�.";

	TextnNextCount = TextInsertCount;
}

void NPCScript::TownGuard_Pass()
{
	NPCTexts.resize(TextInsertCount);
	// ������ �̼���
	NPCTexts[0] = "���⸦ ����Ϸ��� �������� �ʿ���.";
	NPCTexts[1] = "�� �������� ����̴±���. �׷��ٸ� ���\n�� �� ����.";
	// ������ ����
	NPCTexts[2] = "������ �� ����!";
	NPCTexts[3] = "��, �ٸ� ������� ���� ������ 2.27kg�� �� \n���� ���δٴ���...";
	NPCTexts[4] = "�� ������ ������ �ʹ� �̻ڳ�. �ٻ��� �Ӹ���\n�ٰ� �󱼵� ���� �ٸ� ����ε�?";
	NPCTexts[5] = "��¶��, �������� ������ ��������ٰ�. ���\n�� ����!";

	TextnNextCount = TextInsertCount;
}

void NPCScript::Bathwoman()
{
	NPCTexts.resize(TextInsertCount);
	NPCTexts[0] = "������ ���� �㰡������! ���Ⱑ ȸ���˴ϴ�!";

	TextnNextCount = TextInsertCount;
}

void NPCScript::Sky()
{
	NPCTexts.resize(TextInsertCount);
	NPCTexts[0] = "����? ���� ���̾�?";
	NPCTexts[1] = "�������� �ʿ��ϴٰ�? �����̳�.";
	NPCTexts[2] = "�������� �����!"; // ȹ��
	NPCTexts[3] = "������ �׷��� ��ó�� �� �����߸��� �ȵ�!";

	// ������ ���� ��
	NPCTexts[4] = "�� �������� �Ҿ��������!";

	TextnNextCount = TextInsertCount;
}

void NPCScript::Merchant()
{	
	// Script = "��������������������������������������������\n��������������������������������������������";
	NPCTexts.resize(TextInsertCount);
	PlayerTexts.resize(2);
	NPCTexts[0] = "�츮���Կ� �������!";
	NPCTexts[1] = "�������� �缭 ���� �����ϼ���!";
	NPCTexts[2] = "���";
	NPCTexts[3] = "��� (x3)";
	NPCTexts[4] = "ü���� ȸ���� �� �ֽ��ϴ�.";
	NPCTexts[5] = "10";  // ����
	NPCTexts[6] = "25";  // ����
	NPCTexts[7] = "����ũ��";
	NPCTexts[8] = "����ũ�� (x3)";
	NPCTexts[9] = "���ۺ��� ���ư��� ������ ��ö ���� �ڽ��� ��ȣ�ϼ���.";
	NPCTexts[10] = "50";  // ����
	NPCTexts[11] = "120"; // ����
	NPCTexts[12] = "����";
	NPCTexts[13] = "���� (x3)";
	NPCTexts[14] = "���ݿ� �����ϴ� �ֻ��� ��� �����Դϴ�.";
	NPCTexts[15] = "100"; // ����
	NPCTexts[16] = "250"; // ����
	NPCTexts[17] = "���� ����";
	NPCTexts[18] = "���� ����(x3)";
	NPCTexts[19] = "���ݷ��� ������Ű����! �� �� ���� ȿ�ҷ� �����ϴ�ϴ�!";
	NPCTexts[20] = "60";  // ����
	NPCTexts[21] = "150"; // ����
	// ���� ��
	NPCTexts[22] = "�� �������� �����Ͻ� �ǰ���?";
	// ���� �Ϸ�
	NPCTexts[23] = "������! �� �����Ͻ� �� �ֳ���?";
	// �÷��̾�
	PlayerTexts[0] = "��";
	PlayerTexts[1] = "�ƴϿ�";

	TextnNextCount = TextInsertCount;
}

void NPCScript::Squidsmith()
{
	NPCTexts.resize(TextInsertCount);
	PlayerTexts.resize(2);
	// ù ����
	NPCTexts[0] = "��ĿƲ ���� �������� ����̿���!";
	NPCTexts[1] = "�� ���׸İ� ��������� ��Ʈ ������� ���..";
	NPCTexts[2] = "����!";
	NPCTexts[3] = "��!!";
	NPCTexts[4] = "�쿩������!!!";
	NPCTexts[5] = "...�� ��Ʈ�� Ʋ���� �ž�!";
	// ���� ��������
	NPCTexts[6] = "ü�� ĭ�� �ø���?";
	// ��
	NPCTexts[7] = "�̾�������, ü��ĭ�� �ø����� ��Ʈ ���\n�� ���� �ʿ���."; // �� ���� ���� ���
	NPCTexts[8] = "�����غ���!";                                             // ���� ���
	NPCTexts[9] = "��, �� �ִ� ü���� �� ĭ �����߾�!";
	// �ƴϿ�
	NPCTexts[10] = "������ �ٲ����� �𸣴� ���⼭ ��ٸ���!";

	// �÷��̾�
	PlayerTexts[0] = "���� ���ּ���!";
	PlayerTexts[1] = "���� �ȵ�!";

	TextnNextCount = TextInsertCount;
}