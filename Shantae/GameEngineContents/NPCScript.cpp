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

	if (1 == TextCount && true == SKY)
	{
		TextCount = 0;
		Script = "しいぉいぉ";
		TextRender->SetText(Script, 30, "閏顕", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	}
}

void NPCScript::NPCType()
{

}

void NPCScript::Kill()
{
	GameEngineActor* ColActor = TextRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}