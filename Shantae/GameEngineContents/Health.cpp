#include "Health.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

#include "Player.h"

Health* Health::HealthPtr = nullptr;

Health::Health()
{
}

Health::~Health()
{
}

void Health::Start()
{
	HealthPtr = this;

	AnimationRender = CreateRender("Health.Bmp", RenderOrder::UI);
	AnimationRender->CreateAnimation({ .AnimationName = "Heart0",  .ImageName = "Health.bmp", .Start = 4, .End = 4 });
	AnimationRender->CreateAnimation({ .AnimationName = "Heart1",  .ImageName = "Health.bmp", .Start = 3, .End = 3 });
	AnimationRender->CreateAnimation({ .AnimationName = "Heart2",  .ImageName = "Health.bmp", .Start = 2, .End = 2 });
	AnimationRender->CreateAnimation({ .AnimationName = "Heart3",  .ImageName = "Health.bmp", .Start = 1, .End = 1 });
	AnimationRender->CreateAnimation({ .AnimationName = "Heart4",  .ImageName = "Health.bmp", .Start = 0, .End = 0 });
	AnimationRender->SetPosition({30, 30});
	AnimationRender->SetScale({52, 50});
	AnimationRender->EffectCameraOff();

	AnimationRender->ChangeAnimation("Heart4");

	AnimationRender2 = CreateRender("Health.Bmp", RenderOrder::UI);
	AnimationRender2->CreateAnimation({ .AnimationName = "Heart0",  .ImageName = "Health.bmp", .Start = 4, .End = 4 });
	AnimationRender2->CreateAnimation({ .AnimationName = "Heart1",  .ImageName = "Health.bmp", .Start = 3, .End = 3 });
	AnimationRender2->CreateAnimation({ .AnimationName = "Heart2",  .ImageName = "Health.bmp", .Start = 2, .End = 2 });
	AnimationRender2->CreateAnimation({ .AnimationName = "Heart3",  .ImageName = "Health.bmp", .Start = 1, .End = 1 });
	AnimationRender2->CreateAnimation({ .AnimationName = "Heart4",  .ImageName = "Health.bmp", .Start = 0, .End = 0 });
	AnimationRender2->SetPosition({ 90, 30 });
	AnimationRender2->SetScale({ 52, 50 });
	AnimationRender2->EffectCameraOff();

	AnimationRender2->ChangeAnimation("Heart4");
}

void Health::Update(float _DeltaTime)
{
	CurrentPlayerHP();
	HealthControl(PlayerHP);
}

void Health::CurrentPlayerHP()
{
	PlayerHP = Player::MainPlayer->GetPlayerHP();
	PlayerMaxHP = Player::MainPlayer->GetPlayerMaxHP();
}

void Health::HealthControl(int _PlayerHP)
{
	if (8 == _PlayerHP)
	{
		AnimationRender2->ChangeAnimation("Heart4");
	}
	else if (7 == _PlayerHP)
	{
		AnimationRender2->ChangeAnimation("Heart3");
	}
	else if (6 == _PlayerHP)
	{
		AnimationRender2->ChangeAnimation("Heart2");
	}
	else if (5 == _PlayerHP)
	{
		AnimationRender2->ChangeAnimation("Heart1");
	}
	else if (4 == _PlayerHP)
	{
		AnimationRender2->ChangeAnimation("Heart0");
		AnimationRender->ChangeAnimation("Heart4");
	}
	else if (3 == _PlayerHP)
	{
		AnimationRender2->ChangeAnimation("Heart0");
		AnimationRender->ChangeAnimation("Heart3");
	}
	else if (2 == _PlayerHP)
	{
		AnimationRender2->ChangeAnimation("Heart0");
		AnimationRender->ChangeAnimation("Heart2");
	}
	else if (1 == _PlayerHP)
	{
		AnimationRender2->ChangeAnimation("Heart0");
		AnimationRender->ChangeAnimation("Heart1");
	}
	else if (0 == _PlayerHP)
	{
		AnimationRender2->ChangeAnimation("Heart0");
		AnimationRender->ChangeAnimation("Heart0");
	}
}

void Health::CreateNewHealth()
{
	Health* NewHealth = nullptr;
	float4 NewHealthPos = float4::Zero;
	NewHealthPos = GetPos() + (float4::Right * 100);

	NewHealth = GetLevel()->CreateActor<Health>();
	NewHealth->SetPos(NewHealthPos);

	NewHealth1 = true;
}
