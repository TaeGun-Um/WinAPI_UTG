#include "NPCScript.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "BlueTextBox.h"
#include "Inventory.h"
#include "Player.h"
#include "Squidsmith.h"
#include "ShopSelect.h"
#include "ShopBlueBox.h"

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

	if (true == ShopOpen)
	{
		SelectMove(_DeltaTime);
	}
	
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
		TextInsertCount = 23;
		Merchant();
		break;
	case NPCDialogType_Dialog::Squidsmith:
		TextInsertCount = 11;
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

	NPCTexts[0] = "���⸦ ����Ϸ��� �������� �ʿ���.";
	NPCTexts[1] = "�� �������� ����̴±���. �׷��ٸ� ���\n�� �� ����.";
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
	NPCTexts[2] = "[������]�� �����!";
	NPCTexts[3] = "������ �׷��� ��ó�� �� �����߸��� �ȵ�!";
	NPCTexts[4] = "�� �������� �Ҿ��������!";

	TextnNextCount = TextInsertCount;
}

void NPCScript::Merchant()
{	
	// Script = "��������������������������������������������\n��������������������������������������������";
	NPCTexts.resize(TextInsertCount);
	
	NPCTexts[0] = "�츮���Կ� �������!";
	NPCTexts[1] = "���							   10";
	NPCTexts[2] = "��� (x3)						   25";
	NPCTexts[3] = "ü���� ȸ���� �� �ֽ��ϴ�.";
	NPCTexts[4] = "����ũ��						   50";
	NPCTexts[5] = "����ũ�� (x3)					   120";
	NPCTexts[6] = "���ۺ��� ���ư��� ������ ��ö ���� �ڽ��� ��ȣ�ϼ���.";
	NPCTexts[7] = "����							   100";
	NPCTexts[8] = "���� (x3)						   250";
	NPCTexts[9] = "���ݿ� �����ϴ� �ֻ��� ��� �����Դϴ�.";
	NPCTexts[10] = "���� ����					    60";
	NPCTexts[11] = "���� ����(x3)                  150";
	NPCTexts[12] = "���ݷ��� ������Ű����! �� �� ���� ȿ�ҷ� �����ϴ�ϴ�!";

	TextnNextCount = TextInsertCount;
}

void NPCScript::Squidsmith()
{
	NPCTexts.resize(TextInsertCount);
	
	NPCTexts[0] = "��ĿƲ ���� �������� ����̿���!";
	NPCTexts[1] = "�� ���׸İ� ��������� [��Ʈ ����]���� ���..";
	NPCTexts[2] = "����!";
	NPCTexts[3] = "��!!";
	NPCTexts[4] = "�쿩������!!!";
	NPCTexts[5] = "...�� ��Ʈ�� Ʋ���� �ž�!";
	NPCTexts[6] = "ü�� ĭ�� �÷��ٱ�?";
	NPCTexts[7] = "�̾�������, ü�� ĭ�� �ø����� [��Ʈ ����]\n[�� ����]�� �ʿ���.";
	NPCTexts[8] = "�����غ���!";                                             
	NPCTexts[9] = "��, �� �ִ� ü���� �� ĭ �����߾�!";
	NPCTexts[10] = "�̾�������, �� �̻� ü�� ĭ�� �ø� ��\n���ڴ°�?!";

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
			if (20 <= Player::MainPlayer->GetPlayerMaxHP())
			{
				Octopusfull = true;

				if (1 == OctopusfullCount)
				{
					OctopusfullCount = 0;
					TextnNextCount += 3;
				}
			}
			else if (4 <= Player::MainPlayer->GetPlayerOctopus())
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
		else if (true == Octopusfull)
		{
			if (TextnNextCount - TextInsertCount == 5)
			{
				IsTextEnd = true;
				BlueTextBox::DialogTextBox->SetIsOver();
				Player::MainPlayer->SetSquidsmithScriptEnd();
				TextnNextCount -= 2;
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
	if (TextnNextCount - TextInsertCount == 1)
	{
		ShopOpen = true;
		IsTextEnd = true;
	}

	if (true == ShopOpen)
	{
		if (1 == SelectCreate)
		{
			SelectCreate = 0;

			SelectButton = GetLevel()->CreateActor<ShopSelect>();
			SelectButton->SetPos(GetPos());

			ShopBox = GetLevel()->CreateActor<ShopBlueBox>();

			ShopCreate();
		}
		TextRender->Off();
	}
	else if (false == IsTextEnd)
	{
		TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	}
}

void NPCScript::ShopCreate()
{
	ShopScript1 = NPCTexts[1];
	ShopScript2 = NPCTexts[2];
	ShopScript3 = NPCTexts[4];
	ShopScript4 = NPCTexts[3];

	ShopText1 = CreateRender(RenderOrder::UI);
	ShopText1->SetText(ShopScript1, 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	ShopText1->SetPosition(GetPos() + float4::Left * 325 + float4::Up * 200);
	Pos1 = ShopText1->GetPosition() + float4::Right * 280 + float4::Down * 210;
	ShopText1->EffectCameraOff();

	SelectButton->SetPos(Pos1);

	ShopText2 = CreateRender(RenderOrder::UI);
	ShopText2->SetText(ShopScript2, 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	ShopText2->SetPosition(GetPos() + float4::Left * 325 + float4::Up * 150);
	Pos2 = ShopText2->GetPosition() + float4::Right * 280 + float4::Down * 210;
	ShopText2->EffectCameraOff();

	ShopText3 = CreateRender(RenderOrder::UI);
	ShopText3->SetText(ShopScript3, 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	ShopText3->SetPosition(GetPos() + float4::Left * 325 + float4::Up * 100);
	Pos3 = ShopText3->GetPosition() + float4::Right * 280 + float4::Down * 210;
	ShopText3->EffectCameraOff();

	ShopText4 = CreateRender(RenderOrder::UI);
	ShopText4->SetText(ShopScript4, 30, "����", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	ShopText4->SetPosition(GetPos() + float4::Left * 325 + float4::Down * 5);
	ShopText4->EffectCameraOff();
}

void NPCScript::SelectMove(float _DeltaTime)
{
	if (GameEngineInput::IsDown("UpMove"))
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_move.wav");
		BGMPlayer.Volume(0.05f);
		BGMPlayer.LoopCount(1);

		SelectButton->SetPos(Pos1);
	}

	if (GameEngineInput::IsDown("DownMove"))
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_move.wav");
		BGMPlayer.Volume(0.05f);
		BGMPlayer.LoopCount(1);

		SelectButton->SetPos(Pos2);
	}
}