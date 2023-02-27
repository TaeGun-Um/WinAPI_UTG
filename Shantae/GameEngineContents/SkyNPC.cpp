#include "SkyNPC.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "A_Button.h"
#include "Player.h"

SkyNPC::SkyNPC() 
{
}

SkyNPC::~SkyNPC() 
{
}

void SkyNPC::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Sky_L.bmp", .Start = 0, .End = 5, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_L",  .ImageName = "Sky_R.bmp", .Start = 6, .End = 12, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "IdleRev_L",  .ImageName = "Sky_L.bmp", .Start = 21, .End = 26, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Run_L",  .ImageName = "Sky_L.bmp", .Start = 34, .End = 41, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Sky_R.bmp", .Start = 0, .End = 5, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_R",  .ImageName = "Sky_L.bmp", .Start = 6, .End = 12, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "IdleRev_R",  .ImageName = "Sky_R.bmp", .Start = 21, .End = 26, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Run_R",  .ImageName = "Sky_R.bmp", .Start = 34, .End = 41, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 120, 100 });
	BodyCollision->SetPosition({ 0, -50 });

	ChangeState(SkyNPCState::IDLE);
}

void SkyNPC::Update(float _DeltaTime)
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

	CollisionCheck();
	CharacterDirect();
	UpdateState(_DeltaTime);
}

void SkyNPC::Render(float _DeltaTime)
{

}

void SkyNPC::CollisionCheck()
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

void SkyNPC::CharacterDirect()
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

std::string SkyNPC::DirCheck(const std::string_view& _AnimationName)
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