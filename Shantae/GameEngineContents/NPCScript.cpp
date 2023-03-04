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
	Script = "けけけけけけけけけけけけけけけけけけけけけさ\nけけけけけけけけけけけけけけけけけけけけけさ";
	BoxScale = { 650, 300 };
	TextRender->SetText(Script, 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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

	NPCTexts[0] = "食奄辞採斗澗 什朕堂 原聖戚醤.";

	TextnNextCount = TextInsertCount;
}

void NPCScript::TownGuard_Pass()
{
	NPCTexts.resize(TextInsertCount);

	NPCTexts[0] = "食奄研 搭引馬形檎 窒脊装戚 琶推背.";
	NPCTexts[1] = "獲 窒脊装戚 蒸嬢左戚澗姥蟹. 益係陥檎 搭引\n拝 呪 蒸嬢.";
	NPCTexts[2] = "窒脊装 岨 瑳猿!";
	NPCTexts[3] = "人, 陥献 紫寓級精 紫遭 啄生檎 2.27kg精 希 \n蟹亜 左昔陥揮汽...";
	NPCTexts[4] = "獲 神備形 紫遭戚 格巷 戚孜革. 悦紫廃 袴軒拭\n陥亜 杖閏亀 刃穿 陥献 紫寓昔汽?";
	NPCTexts[5] = "嬢其窮, 窒脊装戚 赤生艦 搭引獣佃匝惟. 楳錘\n聖 柵嬢!";
	NPCTexts[6] = "楳錘聖 柵嬢!";

	TextnNextCount = TextInsertCount;
}

void NPCScript::Bathwoman()
{
	NPCTexts.resize(TextInsertCount);

	NPCTexts[0] = "鉦伝拭 倖聖 眼亜左室推! 据奄亜 噺差桔艦陥!";

	TextnNextCount = TextInsertCount;
}

void NPCScript::Sky()
{
	NPCTexts.resize(TextInsertCount);

	NPCTexts[0] = "滋砺? 巷充 析戚醤?";
	NPCTexts[1] = "[窒脊装]戚 琶推馬陥壱? 紺析戚革.";
	NPCTexts[2] = "[窒脊装]聖 条醸陥!";
	NPCTexts[3] = "煽腰拭 益隈揮 依坦軍 暁 諺亜襟軒檎 照掬!";
	NPCTexts[4] = "益 窒脊装精 籍嬢獄軒走原!";

	TextnNextCount = TextInsertCount;
}

void NPCScript::Merchant()
{	
	// Script = "けけけけけけけけけけけけけけけけけけけけけさ\nけけけけけけけけけけけけけけけけけけけけけさ";
	NPCTexts.resize(TextInsertCount);
	
	NPCTexts[0] = "酔軒亜惟拭 嬢辞神室推!";
	NPCTexts[1] = "壱奄							   10";
	NPCTexts[2] = "壱奄 (x3)						   25";
	NPCTexts[3] = "端径聖 噺差拝 呪 赤柔艦陥.";
	NPCTexts[4] = "督戚滴瑳						   50";
	NPCTexts[5] = "督戚滴瑳 (x3)					   120";
	NPCTexts[6] = "桜越桜越 宜焼亜澗 壱搭税 悪旦 姥稽 切重聖 左硲馬室推.";
	NPCTexts[7] = "獄鷺							   100";
	NPCTexts[8] = "獄鷺 (x3)						   250";
	NPCTexts[9] = "因維拭 企誓馬澗 置雌税 号嬢 呪舘脊艦陥.";
	NPCTexts[10] = "佼什斗 酔政					    60";
	NPCTexts[11] = "佼什斗 酔政(x3)                  150";
	NPCTexts[12] = "因維径聖 装亜獣徹室推! 硝 呪 蒸澗 反社稽 亜究馬岩艦陥!";

	TextnNextCount = TextInsertCount;
}

void NPCScript::Squidsmith()
{
	NPCTexts.resize(TextInsertCount);
	
	NPCTexts[0] = "什朕堂 原聖 庚嬢舌昔 企敬戚神神!";
	NPCTexts[1] = "貝 繕益個壱 紫櫛什君錘 [馬闘 庚嬢]級聖 乞焼..";
	NPCTexts[2] = "穿採!";
	NPCTexts[3] = "陥!!";
	NPCTexts[4] = "褐食獄形辞!!!";
	NPCTexts[5] = "...革 馬闘研 堂形匝 暗醤!";
	NPCTexts[6] = "端径 牒聖 潅形匝猿?";
	NPCTexts[7] = "耕照馬走幻, 端径 牒聖 潅軒形檎 [馬闘 庚嬢]\n[革 原軒]亜 琶推背.";
	NPCTexts[8] = "獣拙背瑳猿!";                                             
	NPCTexts[9] = "切, 革 置企 端径戚 廃 牒 装亜梅嬢!";
	NPCTexts[10] = "耕照馬走幻, 希 戚雌 端径 牒聖 潅険 呪\n蒸畏澗杏?!";

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
		TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 6], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 2], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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

			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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

			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
		if (false == IsTextEnd)
		{
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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

			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 6], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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

			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 6], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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

			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 6], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
		if (false == IsTextEnd)
		{
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 6], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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
			TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount + 4], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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
		TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	}
}

void NPCScript::ShopCreate()
{
	ShopScript1 = NPCTexts[1];
	ShopScript2 = NPCTexts[2];
	ShopScript3 = NPCTexts[4];
	ShopScript4 = NPCTexts[3];

	ShopText1 = CreateRender(RenderOrder::UI);
	ShopText1->SetText(ShopScript1, 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	ShopText1->SetPosition(GetPos() + float4::Left * 325 + float4::Up * 200);
	Pos1 = ShopText1->GetPosition() + float4::Right * 280 + float4::Down * 210;
	ShopText1->EffectCameraOff();

	SelectButton->SetPos(Pos1);

	ShopText2 = CreateRender(RenderOrder::UI);
	ShopText2->SetText(ShopScript2, 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	ShopText2->SetPosition(GetPos() + float4::Left * 325 + float4::Up * 150);
	Pos2 = ShopText2->GetPosition() + float4::Right * 280 + float4::Down * 210;
	ShopText2->EffectCameraOff();

	ShopText3 = CreateRender(RenderOrder::UI);
	ShopText3->SetText(ShopScript3, 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	ShopText3->SetPosition(GetPos() + float4::Left * 325 + float4::Up * 100);
	Pos3 = ShopText3->GetPosition() + float4::Right * 280 + float4::Down * 210;
	ShopText3->EffectCameraOff();

	ShopText4 = CreateRender(RenderOrder::UI);
	ShopText4->SetText(ShopScript4, 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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