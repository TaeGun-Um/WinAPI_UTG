#include "TimerCollision.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

TimerCollision* TimerCollision::Timer = nullptr;

TimerCollision::TimerCollision() 
{
}

TimerCollision::~TimerCollision() 
{
}

void TimerCollision::Start()
{
	Timer = this;

	// Collision
	TimerSpot = CreateCollision(CollisionOrder::Spawner);
	TimerSpot->SetDebugRenderType(CT_Rect);
	TimerSpot->SetScale({ 1200, 100 });
	TimerSpot->SetPosition({ 0, 0 });

	SpawnerText.resize(3);
	BoxScale = { 150, 150 };

	SpawnerText[0] = "¿À·ù1";
	SpawnerText[1] = "¿À·ù2";
	SpawnerText[2] = "¿À·ù3";

	TextRender1 = CreateRender(RenderOrder::UI);
	TextRender2 = CreateRender(RenderOrder::UI);
	TextRender3 = CreateRender(RenderOrder::UI);

	TextRender1->SetText(SpawnerText[0], 20, "±¼¸²", TextAlign::Left, RGB(0, 0, 0), BoxScale);
	TextRender2->SetText(SpawnerText[1], 20, "±¼¸²", TextAlign::Left, RGB(255, 0, 255), BoxScale);
	TextRender3->SetText(SpawnerText[2], 20, "±¼¸²", TextAlign::Left, RGB(0, 0, 0), BoxScale);
}

void TimerCollision::Update(float _DeltaTime)
{
	if (0 == TimerSet)
	{
		AccTime += _DeltaTime;
	}

	CollisionCheck();

	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		IsText = !IsText;
	}

	if (true == IsText)
	{
		TextRender1->On();
		TextRender2->On();
		TextRender3->On();
		PositionText();
	}
	else
	{
		TextRender1->Off();
		TextRender2->Off();
		TextRender3->Off();
	}
}

void TimerCollision::CollisionCheck()
{
	if (nullptr != TimerSpot)
	{
		if (true == TimerSpot->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerEffect), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			TimerSet = 0;
		}
	}
}

void TimerCollision::PositionText()
{
	std::string MonsterType = MonsterTYPE;
	std::string Timer = std::to_string(AccTime);
	std::string PossibleTime = "10";

	SpawnerText[0] = MonsterType;
	SpawnerText[1] = Timer;
	SpawnerText[2] = PossibleTime;

	TextRender1->SetText(SpawnerText[0], 20, "±¼¸²", TextAlign::Left, RGB(0, 255, 0), BoxScale);
	TextRender1->SetPosition(float4::Up * 100);

	TextRender2->SetText(SpawnerText[1], 20, "±¼¸²", TextAlign::Left, RGB(255, 0, 0), BoxScale);
	TextRender2->SetPosition(float4::Up * 140);

	TextRender3->SetText(SpawnerText[2], 20, "±¼¸²", TextAlign::Left, RGB(0, 255, 0), BoxScale);
	TextRender3->SetPosition(float4::Up * 120);
}