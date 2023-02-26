#include "AnimationBox_Door.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>

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
			}
			else if ((GetPos().x + 80.0f) <= Player::MainPlayer->GetPos().x)
			{
				Player::MainPlayer->SetMove(float4::Left * 100.0f * _DeltaTime);
			}
		}
	}
}

void AnimationBox_Door::Portal(PortalType _Type)
{
	PortalValue = _Type;

	switch (PortalValue)
	{
	case PortalType::TestRoom:
		GameEngineCore::GetInst()->ChangeLevel("TestRoom");
		break;
	case PortalType::TestRoom2:
		GameEngineCore::GetInst()->ChangeLevel("TestRoom");
		break;
	default:
		break;
	}

}