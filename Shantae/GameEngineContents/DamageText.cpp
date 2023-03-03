#include "DamageText.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

DamageText::DamageText() 
{
}

DamageText::~DamageText() 
{
}

void DamageText::Start()
{
	TextRender = CreateRender(RenderOrder::UI);
	float4 BoxScale = { 50, 50 };
	TextRender->SetText(GetDamage += std::to_string(Player::MainPlayer->GetPlayerDamage()), 25, "±¼¸²", TextAlign::Left, RGB(0, 0, 0), BoxScale);
}

void DamageText::Update(float _DeltaTime)
{
	KillTime += _DeltaTime;

	if (KillTime >= 0.25f)
	{
		SetMove(float4::Up * 25.0f * _DeltaTime);
	}
	
	if (KillTime >= 1.0f)
	{
		Kill();
	}
}

void DamageText::Kill()
{
	GameEngineActor* ColActor = TextRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}