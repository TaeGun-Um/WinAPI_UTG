#include "AnimationBox_Door.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
#include "Player.h"

AnimationBox_Door::AnimationBox_Door() 
{
}

AnimationBox_Door::~AnimationBox_Door() 
{
}

void AnimationBox_Door::Start()
{
	GameEngineRender* Render3 = CreateRender("AnimationBox_Door.Bmp", RenderOrder::BackGround);
	Render3->SetPosition(Render3->GetImage()->GetImageScale().half());
	Render3->SetScale(Render3->GetImage()->GetImageScale());

	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 150, 225 });
	BodyCollision->SetPosition({ 75, 112.5f });
}

void AnimationBox_Door::Update(float _DeltaTime)
{
	PortalCheck(_DeltaTime);
}

void AnimationBox_Door::PortalCheck(float _DeltaTime)
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			IsPortal = true;
		}
		else 
		{
			IsPortal = false;
		}
	}

	if (true == IsPortal)
	{
		if (GameEngineInput::IsDown("UpMove") && PlayerState::IDLE == Player::MainPlayer->GetShantaeState())
		{
			Por = 1;
			Player::MainPlayer->ChangeState(PlayerState::PORTALIN);
			IsPortalIn = true;
		}

		if (PlayerState::PORTALIN == Player::MainPlayer->GetShantaeState())
		{
			IsPortalIn = true;
		}
		else
		{
			IsPortalIn = false;
		}

		if (true == IsPortalIn)
		{
			if ((GetPos().x + 70.0f) >= Player::MainPlayer->GetPos().x)
			{
				Player::MainPlayer->SetMove(float4::Right * 100.0f * _DeltaTime);
				GetLevel()->SetCameraMove(float4::Right * 100.0f * _DeltaTime);
			}
			else if ((GetPos().x + 80.0f) <= Player::MainPlayer->GetPos().x)
			{
				Player::MainPlayer->SetMove(float4::Left * 100.0f * _DeltaTime);
				GetLevel()->SetCameraMove(float4::Left * 100.0f * _DeltaTime);
			}
		}

		if (PlayerState::PORTALING == Player::MainPlayer->GetShantaeState())
		{
			if (1 == Por)
			{
				Portal();
				Por = 0;
			}
			
		}
	}
}

void AnimationBox_Door::Portal()
{
	switch (PortalValue)
	{
	case PortalType::TestRoom:
		GameEngineCore::GetInst()->ChangeLevel("TestRoom");
		break;
	case PortalType::TestRoom2:
		GameEngineCore::GetInst()->ChangeLevel("TestRoom2");
		break;
	default:
		break;
	}

}