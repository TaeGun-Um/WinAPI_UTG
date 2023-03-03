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
	BoxScale = { 650, 500 };
	TextRender->SetText(Script, 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	TextRender->EffectCameraOff();
}

void NPCScript::Update(float _DeltaTime)
{
	if (1 == TextCount)
	{
		TextCount = 0;
	}
}

void NPCScript::Kill()
{
	GameEngineActor* ColActor = TextRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}