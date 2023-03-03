#include "NPCScript.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
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
	NPCType();
	if (1 == TextCount)
	{
		TextCount = 0;
		TextRender->SetText(Script, 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	}
}

void NPCScript::NPCType()
{
	switch (NPCValue)
	{
	case NPCDialogType_Dialog::Sky:
		Script = "Sky";
		break;
	case NPCDialogType_Dialog::Bathwoman:
		Script = "Bathwoman";
		break;
	case NPCDialogType_Dialog::Merchant:
		Script = "Merchant";
		break;
	case NPCDialogType_Dialog::Squidsmith:
		Script = "Squidsmith";
		break;
	case NPCDialogType_Dialog::Town_Guard:
		Script = "Town_Guard";
		break;
	case NPCDialogType_Dialog::Town_Guard_Pass:
		Script = "Town_Guard_Pass";
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