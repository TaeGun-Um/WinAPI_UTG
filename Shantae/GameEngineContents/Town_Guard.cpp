#include "Town_Guard.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "A_Button.h"
#include "Player.h"

Town_Guard::Town_Guard() 
{
}

Town_Guard::~Town_Guard() 
{
}

void Town_Guard::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Town Guard_L.bmp", .Start = 0, .End = 6, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_L",  .ImageName = "Town Guard_R.bmp", .Start = 7, .End = 10, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Town Guard_R.bmp", .Start = 0, .End = 6, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_R",  .ImageName = "Town Guard_L.bmp", .Start = 7, .End = 10, .InterTime = 0.1f });


	BodyCollision = CreateCollision(CollisionOrder::NPC);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 120, 100 });
	BodyCollision->SetPosition({ 0, -50 });

	ChangeState(Town_GuardState::IDLE);
}

void Town_Guard::Update(float _DeltaTime)
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

void Town_Guard::Render(float _DeltaTime)
{

}

void Town_Guard::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			AButton->On();

			if (true == PassGuard)
			{
				Player::MainPlayer->NPCType(NPCDialogType::Town_Guard_Pass);
			}
			else
			{
				Player::MainPlayer->NPCType(NPCDialogType::Town_Guard);
			}
		}
		else
		{
			AButton->Off();
		}
	}
}

void Town_Guard::CharacterDirect()
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

std::string Town_Guard::DirCheck(const std::string_view& _AnimationName)
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