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
	Script = "けけけけけけけけけけけけけけけけけけけけけさ\nけけけけけけけけけけけけけけけけけけけけけさ";
	BoxScale = { 650, 300 };
	TextRender->SetText(Script, 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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
		TextRender->SetText(NPCTexts[TextnNextCount - TextInsertCount], 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
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
	NPCTexts[0] = "食奄辞採斗澗 什朕堂 原聖戚醤.";

	TextnNextCount = TextInsertCount;
}

void NPCScript::TownGuard_Pass()
{
	NPCTexts.resize(TextInsertCount);
	// 窒脊装 耕社走
	NPCTexts[0] = "食奄研 搭引馬形檎 窒脊装戚 琶推背.";
	NPCTexts[1] = "獲 窒脊装戚 蒸嬢左戚澗姥蟹. 益係陥檎 搭引\n拝 呪 蒸嬢.";
	// 窒脊装 社走
	NPCTexts[2] = "窒脊装 岨 瑳猿!";
	NPCTexts[3] = "人, 陥献 紫寓級精 紫遭 啄生檎 2.27kg精 希 \n蟹亜 左昔陥揮汽...";
	NPCTexts[4] = "獲 神備形 紫遭戚 格巷 戚孜革. 悦紫廃 袴軒拭\n陥亜 杖閏亀 刃穿 陥献 紫寓昔汽?";
	NPCTexts[5] = "嬢其窮, 窒脊装戚 赤生艦 搭引獣佃匝惟. 楳錘\n聖 柵嬢!";

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
	NPCTexts[1] = "窒脊装戚 琶推馬陥壱? 紺析戚革.";
	NPCTexts[2] = "窒脊装聖 条醸陥!"; // 塙究
	NPCTexts[3] = "煽腰拭 益隈揮 依坦軍 暁 諺亜襟軒檎 照掬!";

	// 窒脊装 呪敬 板
	NPCTexts[4] = "益 窒脊装精 籍嬢獄軒走原!";

	TextnNextCount = TextInsertCount;
}

void NPCScript::Merchant()
{	
	// Script = "けけけけけけけけけけけけけけけけけけけけけさ\nけけけけけけけけけけけけけけけけけけけけけさ";
	NPCTexts.resize(TextInsertCount);
	PlayerTexts.resize(2);
	NPCTexts[0] = "酔軒亜惟拭 嬢辞神室推!";
	NPCTexts[1] = "広製生稽 紫辞 儀聖 箭鉦馬室推!";
	NPCTexts[2] = "壱奄";
	NPCTexts[3] = "壱奄 (x3)";
	NPCTexts[4] = "端径聖 噺差拝 呪 赤柔艦陥.";
	NPCTexts[5] = "10";  // 亜維
	NPCTexts[6] = "25";  // 亜維
	NPCTexts[7] = "督戚滴瑳";
	NPCTexts[8] = "督戚滴瑳 (x3)";
	NPCTexts[9] = "桜越桜越 宜焼亜澗 壱搭税 悪旦 姥稽 切重聖 左硲馬室推.";
	NPCTexts[10] = "50";  // 亜維
	NPCTexts[11] = "120"; // 亜維
	NPCTexts[12] = "獄鷺";
	NPCTexts[13] = "獄鷺 (x3)";
	NPCTexts[14] = "因維拭 企誓馬澗 置雌税 号嬢 呪舘脊艦陥.";
	NPCTexts[15] = "100"; // 亜維
	NPCTexts[16] = "250"; // 亜維
	NPCTexts[17] = "佼什斗 酔政";
	NPCTexts[18] = "佼什斗 酔政(x3)";
	NPCTexts[19] = "因維径聖 装亜獣徹室推! 硝 呪 蒸澗 反社稽 亜究馬岩艦陥!";
	NPCTexts[20] = "60";  // 亜維
	NPCTexts[21] = "150"; // 亜維
	// 識澱 獣
	NPCTexts[22] = "戚 焼戚奴聖 姥古馬叔 闇亜推?";
	// 姥古 刃戟
	NPCTexts[23] = "壱原趨推! 暁 姥古馬叔 依 赤蟹推?";
	// 巴傾戚嬢
	PlayerTexts[0] = "森";
	PlayerTexts[1] = "焼艦推";

	TextnNextCount = TextInsertCount;
}

void NPCScript::Squidsmith()
{
	NPCTexts.resize(TextInsertCount);
	PlayerTexts.resize(2);
	// 湛 繕酔
	NPCTexts[0] = "什朕堂 原聖 庚嬢舌昔 企敬戚神神!";
	NPCTexts[1] = "貝 繕益個壱 紫櫛什君錘 馬闘 庚嬢級聖 乞焼..";
	NPCTexts[2] = "穿採!";
	NPCTexts[3] = "陥!!";
	NPCTexts[4] = "褐食獄形辞!!!";
	NPCTexts[5] = "...革 馬闘研 堂形匝 暗醤!";
	// 戚板 霜税誓岩
	NPCTexts[6] = "端径 牒聖 潅険掘?";
	// 森
	NPCTexts[7] = "耕照馬走幻, 端径牒聖 潅軒形檎 馬闘 庚嬢亜\n革 原軒 琶推背."; // 革 原軒 蒸聖 井酔
	NPCTexts[8] = "獣拙背瑳猿!";                                             // 赤聖 井酔
	NPCTexts[9] = "切, 革 置企 端径戚 廃 牒 装亜梅嬢!";
	// 焼艦神
	NPCTexts[10] = "持唖戚 郊介走亀 乞牽艦 食奄辞 奄陥険惟!";

	// 巴傾戚嬢
	PlayerTexts[0] = "雁舌 背爽室推!";
	PlayerTexts[1] = "箭企 照掬!";

	TextnNextCount = TextInsertCount;
}