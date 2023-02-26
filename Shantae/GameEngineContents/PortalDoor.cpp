#include "PortalDoor.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Scuttle.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "BlackBox.h"

BlackBox* PortalDoor::BBox = nullptr;
int PortalDoor::BBoxCount = 1;

PortalDoor::PortalDoor()
{
}

PortalDoor::~PortalDoor()
{
}

void PortalDoor::Start()
{
	GameEngineRender* Render3 = CreateRender("AnimationBox_Door.Bmp", RenderOrder::Object);
	Render3->SetPosition(Render3->GetImage()->GetImageScale().half());
	Render3->SetScale(Render3->GetImage()->GetImageScale());
	Render3->Off();

	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 150, 225 });
	BodyCollision->SetPosition({ 75, 112.5f });
}

void PortalDoor::Update(float _DeltaTime)
{
	PortalCheck(_DeltaTime);
}

void PortalDoor::PortalCheck(float _DeltaTime)
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
			Player::MainPlayer->SetPortalEnd(false);
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
			if (240 <= Player::MainPlayer->GetShataeAnimationRender()->GetFrame())
			{
				BlackBoxInAnimation();
			}

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
			if (1 == Por && true == BBox->GetIsFadeInOver())
			{
				Portal();
				Por = 0;
			}
		}
	}
}

void PortalDoor::Portal()
{
	switch (PortalValue)
	{
	case PortalType::TestRoom:
		GameEngineCore::GetInst()->ChangeLevel("TestRoom");
		break;
	case PortalType::TestRoom2:
		GameEngineCore::GetInst()->ChangeLevel("TestRoom2");
		break;
	case PortalType::UncleRoom:
		Scuttle::ScuttleBGMPlayer.Stop();
		Scuttle::ScuttlePalyer = false;
		GameEngineCore::GetInst()->ChangeLevel("UncleRoom");
		break;
	case PortalType::Shop:
		Scuttle::ScuttleBGMPlayer.Stop();
		Scuttle::ScuttlePalyer = false;
		GameEngineCore::GetInst()->ChangeLevel("Shop");
		break;
	case PortalType::Spa:
		Scuttle::ScuttlePalyer = true;
		GameEngineCore::GetInst()->ChangeLevel("Spa");
		break;
	case PortalType::Smith:
		Scuttle::ScuttleBGMPlayer.Stop();
		Scuttle::ScuttlePalyer = false;
		GameEngineCore::GetInst()->ChangeLevel("Smith");
		break;
	case PortalType::SkyRoom:
		Scuttle::ScuttleBGMPlayer.Stop();
		Scuttle::ScuttlePalyer = false;
		GameEngineCore::GetInst()->ChangeLevel("SkyRoom");
		break;
	case PortalType::SaveRoom:
		Scuttle::ScuttlePalyer = true;
		GameEngineCore::GetInst()->ChangeLevel("SaveRoom");
		break;
	default:
		break;
	}
}

void PortalDoor::BlackBoxInAnimation()
{
	if (1 == BBoxCount)
	{
		BBoxCount = 0;
		BBox = GetLevel()->CreateActor<BlackBox>();
		BBox->FadeInStart(2, 0);
	}
}

void PortalDoor::InBoxKill()
{
	if (nullptr != BBox)
	{
		BBox->Death();
		BBox = nullptr;
		BBoxCount = 1;
	}
}