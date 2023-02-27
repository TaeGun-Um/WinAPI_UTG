#include "Squidsmith.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "A_Button.h"
#include "Player.h"

Squidsmith::Squidsmith() 
{
}

Squidsmith::~Squidsmith() 
{
}

void Squidsmith::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 750, 750 });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Squidsmith_L.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_L",  .ImageName = "Squidsmith_R.bmp", .Start = 8, .End = 16, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Squidsmith_R.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_R",  .ImageName = "Squidsmith_L.bmp", .Start = 8, .End = 16, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Enchant",  .ImageName = "Squidsmith_L.bmp", .Start = 17, .End = 86, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 120, 100 });
	BodyCollision->SetPosition({ 0, -50 });

	ChangeState(SquidsmithState::IDLE);
}

void Squidsmith::Update(float _DeltaTime)
{
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

	CollisionCheck();
	CharacterDirect();
	UpdateState(_DeltaTime);
}

void Squidsmith::Render(float _DeltaTime)
{

}

void Squidsmith::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			AButton->On();
		}
		else
		{
			AButton->Off();
		}
	}
}

void Squidsmith::CharacterDirect()
{
	float interval = Player::MainPlayer->GetPos().x - GetPos().x;

	if (0.0f >= interval)
	{
		MoveDirect = true;
	}
	else
	{
		MoveDirect = false;
	}
}

std::string Squidsmith::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;
	AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);

	if (true == MoveDirect)
	{
		DirString = "_L";
	}
	else if (false == MoveDirect)
	{
		DirString = "_R";
	}

	if (PrevDirString != DirString)
	{
		Isturn = true;
	}

	return DirString;
}