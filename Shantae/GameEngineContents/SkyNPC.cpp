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
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });

	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 120, 100 });
	BodyCollision->SetPosition({ 0, -50 });
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
		AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);
	}

	return DirString;
}