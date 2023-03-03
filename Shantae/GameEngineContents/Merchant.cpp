#include "Merchant.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "Player.h"
#include "A_Button.h"

Merchant::Merchant() 
{
}

Merchant::~Merchant() 
{
}

void Merchant::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle",  .ImageName = "Merchant.bmp", .Start = 0, .End = 4, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Run",  .ImageName = "Merchant.bmp", .Start = 5, .End = 9, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::NPC);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 120, 100 });
	BodyCollision->SetPosition({ 0, -50 });

	AnimationRender->ChangeAnimation("Idle");
}

void Merchant::Update(float _DeltaTime)
{
	if (1 == CurrentPosCount)
	{
		CurrentPosCount = 0;
		CurrentPos = GetPos();

		if (1 == CreateAButtion)
		{
			CreateAButtion = 0;
			AButton = nullptr;
			float4 AButtonPos = float4::Zero;
			AButtonPos = GetPos() + (float4::Up * 180);

			AButton = GetLevel()->CreateActor<A_Button>();
			AButton->SetPos(AButtonPos);
			AButton->Off();
		}
	}

	if (true == IsRun)
	{
		Run(_DeltaTime);
	}

	CollisionCheck();
	DirectCheckForKill();
}

void Merchant::Render(float _DeltaTime)
{

}

void Merchant::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			AButton->On();
			Player::MainPlayer->NPCType(NPCDialogType::Merchant);
		}
		else
		{
			AButton->Off();
		}
	}
}

void Merchant::Run(float _DeltaTime)
{
	AnimationRender->ChangeAnimation("Run");
	BodyCollision->Off();
	SetMove(float4::Left * RunSpeed * _DeltaTime);
}

void Merchant::DirectCheckForKill()
{
	float4 Pos = CurrentPos + (float4::Left * 2500);

	if (GetPos().x <= Pos.x)
	{
		Kill();
	}
}

void Merchant::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}