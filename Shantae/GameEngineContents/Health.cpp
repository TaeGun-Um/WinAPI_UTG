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

	Heart1 = CreateRender("Health.Bmp", RenderOrder::UI);
	Heart1->CreateAnimation({ .AnimationName = "Heart0",  .ImageName = "Health.bmp", .Start = 4, .End = 4 });
	Heart1->CreateAnimation({ .AnimationName = "Heart1",  .ImageName = "Health.bmp", .Start = 3, .End = 3 });
	Heart1->CreateAnimation({ .AnimationName = "Heart2",  .ImageName = "Health.bmp", .Start = 2, .End = 2 });
	Heart1->CreateAnimation({ .AnimationName = "Heart3",  .ImageName = "Health.bmp", .Start = 1, .End = 1 });
	Heart1->CreateAnimation({ .AnimationName = "Heart4",  .ImageName = "Health.bmp", .Start = 0, .End = 0 });
	Heart1->SetPosition({30, 30});
	Heart1->SetScale({52, 50});
	Heart1->EffectCameraOff();

	Heart1->ChangeAnimation("Heart4");

	Heart2 = CreateRender("Health.Bmp", RenderOrder::UI);
	Heart2->CreateAnimation({ .AnimationName = "Heart0",  .ImageName = "Health.bmp", .Start = 4, .End = 4 });
	Heart2->CreateAnimation({ .AnimationName = "Heart1",  .ImageName = "Health.bmp", .Start = 3, .End = 3 });
	Heart2->CreateAnimation({ .AnimationName = "Heart2",  .ImageName = "Health.bmp", .Start = 2, .End = 2 });
	Heart2->CreateAnimation({ .AnimationName = "Heart3",  .ImageName = "Health.bmp", .Start = 1, .End = 1 });
	Heart2->CreateAnimation({ .AnimationName = "Heart4",  .ImageName = "Health.bmp", .Start = 0, .End = 0 });
	Heart2->SetPosition({ 90, 30 });
	Heart2->SetScale({ 52, 50 });
	Heart2->EffectCameraOff();

	Heart2->ChangeAnimation("Heart4");

	Heart3 = CreateRender("Health.Bmp", RenderOrder::UI);
	Heart3->CreateAnimation({ .AnimationName = "Heart0",  .ImageName = "Health.bmp", .Start = 4, .End = 4 });
	Heart3->CreateAnimation({ .AnimationName = "Heart1",  .ImageName = "Health.bmp", .Start = 3, .End = 3 });
	Heart3->CreateAnimation({ .AnimationName = "Heart2",  .ImageName = "Health.bmp", .Start = 2, .End = 2 });
	Heart3->CreateAnimation({ .AnimationName = "Heart3",  .ImageName = "Health.bmp", .Start = 1, .End = 1 });
	Heart3->CreateAnimation({ .AnimationName = "Heart4",  .ImageName = "Health.bmp", .Start = 0, .End = 0 });
	Heart3->SetPosition({ 150, 30 });
	Heart3->SetScale({ 52, 50 });
	Heart3->EffectCameraOff();
	Heart3->Off();

	Heart3->ChangeAnimation("Heart4");

	Heart4 = CreateRender("Health.Bmp", RenderOrder::UI);
	Heart4->CreateAnimation({ .AnimationName = "Heart0",  .ImageName = "Health.bmp", .Start = 4, .End = 4 });
	Heart4->CreateAnimation({ .AnimationName = "Heart1",  .ImageName = "Health.bmp", .Start = 3, .End = 3 });
	Heart4->CreateAnimation({ .AnimationName = "Heart2",  .ImageName = "Health.bmp", .Start = 2, .End = 2 });
	Heart4->CreateAnimation({ .AnimationName = "Heart3",  .ImageName = "Health.bmp", .Start = 1, .End = 1 });
	Heart4->CreateAnimation({ .AnimationName = "Heart4",  .ImageName = "Health.bmp", .Start = 0, .End = 0 });
	Heart4->SetPosition({ 210, 30 });
	Heart4->SetScale({ 52, 50 });
	Heart4->EffectCameraOff();
	Heart4->Off();

	Heart4->ChangeAnimation("Heart4");

	Heart5 = CreateRender("Health.Bmp", RenderOrder::UI);
	Heart5->CreateAnimation({ .AnimationName = "Heart0",  .ImageName = "Health.bmp", .Start = 4, .End = 4 });
	Heart5->CreateAnimation({ .AnimationName = "Heart1",  .ImageName = "Health.bmp", .Start = 3, .End = 3 });
	Heart5->CreateAnimation({ .AnimationName = "Heart2",  .ImageName = "Health.bmp", .Start = 2, .End = 2 });
	Heart5->CreateAnimation({ .AnimationName = "Heart3",  .ImageName = "Health.bmp", .Start = 1, .End = 1 });
	Heart5->CreateAnimation({ .AnimationName = "Heart4",  .ImageName = "Health.bmp", .Start = 0, .End = 0 });
	Heart5->SetPosition({ 270, 30 });
	Heart5->SetScale({ 52, 50 });
	Heart5->EffectCameraOff();
	Heart5->Off();

	Heart5->ChangeAnimation("Heart4");
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

	CreateNewHealth();
}

void Health::HealthControl(int _PlayerHP)
{
	if (8 == _PlayerHP)
	{
		Heart2->ChangeAnimation("Heart4");
		Heart1->ChangeAnimation("Heart4");
	}
	else if (7 == _PlayerHP)
	{
		Heart2->ChangeAnimation("Heart3");
		Heart1->ChangeAnimation("Heart4");
	}
	else if (6 == _PlayerHP)
	{
		Heart2->ChangeAnimation("Heart2");
		Heart1->ChangeAnimation("Heart4");
	}
	else if (5 == _PlayerHP)
	{
		Heart2->ChangeAnimation("Heart1");
		Heart1->ChangeAnimation("Heart4");
	}
	else if (4 == _PlayerHP)
	{
		Heart2->ChangeAnimation("Heart0");
		Heart1->ChangeAnimation("Heart4");
	}
	else if (3 == _PlayerHP)
	{
		Heart2->ChangeAnimation("Heart0");
		Heart1->ChangeAnimation("Heart3");
	}
	else if (2 == _PlayerHP)
	{
		Heart2->ChangeAnimation("Heart0");
		Heart1->ChangeAnimation("Heart2");
	}
	else if (1 == _PlayerHP)
	{
		Heart2->ChangeAnimation("Heart0");
		Heart1->ChangeAnimation("Heart1");
	}
	else if (0 == _PlayerHP)
	{
		Heart2->ChangeAnimation("Heart0");
		Heart1->ChangeAnimation("Heart0");
	}
}

void Health::CreateNewHealth()
{
	if (20 <= Player::MainPlayer->GetNewMaxHP())
	{
		Heart5->On();
		Heart4->On();
		Heart3->On();
		Player::MainPlayer->SetPlayerMaxHP(Player::MainPlayer->GetNewMaxHP());
		Player::MainPlayer->SetPlayerHP(Player::MainPlayer->GetNewMaxHP());
	}
	if (16 <= Player::MainPlayer->GetNewMaxHP())
	{
		Heart4->On();
		Heart3->On();
		Player::MainPlayer->SetPlayerMaxHP(Player::MainPlayer->GetNewMaxHP());
		Player::MainPlayer->SetPlayerHP(Player::MainPlayer->GetNewMaxHP());
	}
	else if (12 <= Player::MainPlayer->GetNewMaxHP())
	{
		Heart3->On();
		Player::MainPlayer->SetPlayerMaxHP(Player::MainPlayer->GetNewMaxHP());
		Player::MainPlayer->SetPlayerHP(Player::MainPlayer->GetNewMaxHP());
	}
}
