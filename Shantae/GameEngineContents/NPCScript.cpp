#include "NPCScript.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "BlueTextBox.h"
#include "Inventory.h"
#include "Player.h"
#include "Squidsmith.h"

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
	if (1 == NPCCount)
	{
		NPCCount = 0;
		NPCType();
	}

	DialogType();
}

void NPCScript::NPCType()
{
	switch (NPCValue)
	{
	case NPCDialogType_Dialog::Sky:
		TextInsertCount = 5;
		Sky();
		break;
	case NPCDialogType_Dialog::Bathwoman:
		TextInsertCount = 1;
		Bathwoman();
		break;
	case NPCDialogType_Dialog::Merchant:
		TextInsertCount = 24;
		Merchant();
		break;
	case NPCDialogType_Dialog::Squidsmith:
		TextInsertCount = 10;
		Squidsmith();
		break;
	case NPCDialogType_Dialog::Town_Guard:
		TextInsertCount = 1;
		TownGuard();
		break;
	case NPCDialogType_Dialog::Town_Guard_Pass:
		TextInsertCount = 7;
		TownGuard_Pass();
		break;
	default:
		break;
	}
}

void NPCScript::DialogType()
{
	switch (NPCValue)
	{
	case NPCDialogType_Dialog::Sky:
		SkyCreate();
		break;
	case NPCDialogType_Dialog::Bathwoman:
		NormalTextCreate();
		break;
	case NPCDialogType_Dialog::Merchant:
		MerchantCreate();
		break;
	case NPCDialogType_Dialog::Squidsmith:
		SquidsmithCreate();
		break;
	case NPCDialogType_Dialog::Town_Guard:
		NormalTextCreate();
		break;
	case NPCDialogType_Dialog::Town_Guard_Pass:
		TownGuard_PassCreate();
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
	NPCTexts[6] = "����� ����!";

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
	NPCTexts[1] = "[������]�� �ʿ��ϴٰ�? �����̳�.";
	NPCTexts[2] = "[������]�� �����!"; // ȹ��
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
	// ù ����
	NPCTexts[0] = "��ĿƲ ���� �������� ����̿���!";
	NPCTexts[1] = "�� ���׸İ� ��������� [��Ʈ ����]��\n�� ���..";
	NPCTexts[2] = "����!";
	NPCTexts[3] = "��!!";
	NPCTexts[4] = "�쿩������!!!";
	NPCTexts[5] = "...�� ��Ʈ�� Ʋ���� �ž�!";

	NPCTexts[6] = "ü�� ĭ�� �÷��ٱ�?";
	
	NPCTexts[7] = "�̾�������, ü��ĭ�� �ø����� ��Ʈ ���\n�� ���� �ʿ���."; // �� ���� ���� ���

	NPCTexts[8] = "�����غ���!";                                             // ���� ���
	NPCTexts[9] = "��, �� �ִ� ü���� �� ĭ �����߾�!";

	TextnNextCount = TextInsertCount;
}

void NPCScript::NormalTextCreate()
{
	if (TextnNextCount - TextInsertCount >= TextInsertCount)
	{
		IsTextEnd = true;
		BlueTextBox::DialogTextBox->SetIsOver();
	}

	if (false == IsTextEnd)
	{
		TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	}
}

void NPCScript::TownGuard_PassCreate()
{
	if (0 == Player::MainPlayer->GetPlayerIDCard())
	{
		if (TextnNextCount - TextInsertCount == 2)
		{
			IsTextEnd = true;
			BlueTextBox::DialogTextBox->SetIsOver();
		}

		if (false == IsTextEnd)
		{
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
	}
	else if (true == Player::MainPlayer->GetTownGuardScriptEnd())
	{
		if (TextnNextCount - TextInsertCount == 1)
		{
			IsTextEnd = true;
			BlueTextBox::DialogTextBox->SetIsOver();
		}

		if (false == IsTextEnd)
		{
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 6], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
	}
	else if (0 != Player::MainPlayer->GetPlayerIDCard())
	{
		if (TextnNextCount - TextInsertCount == 4)
		{
			IsTextEnd = true;
			BlueTextBox::DialogTextBox->SetIsOver();
			Player::MainPlayer->SetTownGuardScriptEnd();
			Player::MainPlayer->SetScuttlePass();
		}

		if (false == IsTextEnd)
		{
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 2], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
	}
}

void NPCScript::SquidsmithCreate()
{
	if (false == Player::MainPlayer->GetSquidsmithScriptEnd())
	{
		if (TextnNextCount - TextInsertCount == 7)
		{
			if (4 <= Player::MainPlayer->GetPlayerOctopus())
			{
				Octopusenough = true;

				if (1 == OctopusTextPlus)
				{
					OctopusTextPlus = 0;
					++TextnNextCount;
				}
			}
			else if (4 > Player::MainPlayer->GetPlayerOctopus())
			{
				Octopusless = true;
			}
		}

		if (true == Octopusless)
		{
			if (TextnNextCount - TextInsertCount == 8)
			{
				IsTextEnd = true;
				BlueTextBox::DialogTextBox->SetIsOver();
				Player::MainPlayer->SetSquidsmithScriptEnd();
			}

			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
		else if (true == Octopusenough)
		{
			if (TextnNextCount - TextInsertCount == 9 && 1 == OctopusAction)
			{
				OctopusAction = 0;
				BlueTextBox::DialogTextBox->SetHeartAction(true);
			}

			if (TextnNextCount - TextInsertCount == 10)
			{
				IsTextEnd = true;
				BlueTextBox::DialogTextBox->SetIsOver();
				Player::MainPlayer->SetSquidsmithScriptEnd();
				--TextnNextCount;
			}

			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
		if (false == IsTextEnd)
		{
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
	}
	else
	{
		if (TextnNextCount - TextInsertCount == 1)
		{
			if (4 > Player::MainPlayer->GetPlayerOctopus())
			{
				Octopusenough = true;

				if (1 == OctopusTextPlus)
				{
					OctopusTextPlus = 0;
					++TextnNextCount;
				}
			}
			else if (4 <= Player::MainPlayer->GetPlayerOctopus())
			{
				Octopusless = true;
			}
		}

		if (true == Octopusless)
		{
			if (TextnNextCount - TextInsertCount == 2)
			{
				IsTextEnd = true;
				BlueTextBox::DialogTextBox->SetIsOver();
				Player::MainPlayer->SetSquidsmithScriptEnd();
			}

			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 6], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
		else if (true == Octopusenough)
		{
			if (TextnNextCount - TextInsertCount == 3 && 1 == OctopusAction)
			{
				OctopusAction = 0;
				BlueTextBox::DialogTextBox->SetHeartAction(true);
			}

			if (TextnNextCount - TextInsertCount == 4)
			{
				IsTextEnd = true;
				BlueTextBox::DialogTextBox->SetIsOver();
				Player::MainPlayer->SetSquidsmithScriptEnd();
				--TextnNextCount;
			}

			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 6], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
		if (false == IsTextEnd)
		{
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 6], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
	}
}

void NPCScript::SkyCreate()
{
	if (false == Player::MainPlayer->GetSkyScriptEnd())
	{
		if (TextnNextCount - TextInsertCount + 1 >= TextInsertCount)
		{
			IsTextEnd = true;
			BlueTextBox::DialogTextBox->SetIsOver();
			Player::MainPlayer->SetSkyScriptEnd();
		}

		if (false == IsTextEnd)
		{
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}

		if (TextnNextCount - TextInsertCount + 3 == TextInsertCount)
		{
			if (1 == IDCardCreate)
			{
				IDCardCreate = 0;

				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_gem.wav");
				BGMPlayer.Volume(0.1f);
				BGMPlayer.LoopCount(1);

				Player::MainPlayer->SetPlayerIDCard(1);
				Player::MainPlayer->SetItemEquip(true);
				Inventory::PlayerInven->SetEquipItem("IDCard");
			}
		}
	}
	else
	{
		if (TextnNextCount - TextInsertCount == 1)
		{
			IsTextEnd = true;
			BlueTextBox::DialogTextBox->SetIsOver();
		}

		if (false == IsTextEnd)
		{
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 4], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
	}
}

void NPCScript::MerchantCreate()
{
	if (TextnNextCount - TextInsertCount >= TextInsertCount)
	{
		IsTextEnd = true;
		BlueTextBox::DialogTextBox->SetIsOver();
	}

	if (false == IsTextEnd)
	{
		TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	}
}