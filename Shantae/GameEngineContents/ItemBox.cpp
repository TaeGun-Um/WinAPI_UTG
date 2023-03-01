#include "ItemBox.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

#include "Heart_Octopus.h"

ItemBox::ItemBox() 
{
}

ItemBox::~ItemBox() 
{
}

void ItemBox::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Close",  .ImageName = "ItemBox.bmp", .Start = 0, .End = 0, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Open",  .ImageName = "ItemBox.bmp", .Start = 1, .End = 4, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Opening",  .ImageName = "ItemBox.bmp", .Start = 4, .End = 4, .InterTime = 0.1f, .Loop = false });

	BodyCollision = CreateCollision(CollisionOrder::Item);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 80, 80 });
	BodyCollision->SetPosition({ 0, -40 });

	AnimationRender->ChangeAnimation("Close");
}

void ItemBox::Update(float _DeltaTime)
{
	MoveCalculation(_DeltaTime);
	CollisionCheck(_DeltaTime);

	if (true == IsHit)
	{
		BoxOpen();
	}
}

void ItemBox::Render(float _DeltaTime)
{

}

// 중력, 점프, 맵타일
void ItemBox::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  중력  ///////////////////////////////////////////////////

	MoveDir += float4::Down * 1500.0f * _DeltaTime;

	/////////////////////////////////////////////////// 맵타일 ///////////////////////////////////////////////////

	NextPos = GetPos() + MoveDir * _DeltaTime;

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir = float4::Zero;
	}

	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir = float4::Zero;
	}

	SetMove(MoveDir * _DeltaTime);
}

void ItemBox::CollisionCheck(float _DeltaTime)
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			BodyCollision->Off();

			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Strike_enemy.mp3");
			BGMPlayer.Volume(0.075f);
			BGMPlayer.LoopCount(1);

			IsHit = true;
		}
	}
}

void ItemBox::BoxOpen()
{
	if (1 == Open)
	{
		Open = 0;
		AnimationRender->ChangeAnimation("Open");
	}
	
	if (true == AnimationRender->IsAnimationEnd())
	{
		if (1 == CreateCount)
		{
			CreateCount = 0;
			AnimationRender->ChangeAnimation("Opening");
			CreateItem();
		}
	}
}

void ItemBox::CreateItem()
{
	switch (ItemValue)
	{
	case OfItemBox::OCT:
	{
		Heart_Octopus* Octopus = nullptr;
		float4 OctPos = GetPos() + float4::Up * 50;

		Octopus = GetLevel()->CreateActor<Heart_Octopus>();
		Octopus->SetPos(OctPos);
		Octopus->SetColMap(ColMap);
	}
	break;
	case OfItemBox::BUB:
		
		break;
	case OfItemBox::PIKE:
		
		break;
	case OfItemBox::MILK:
		
		break;
	case OfItemBox::MEAT:
		
		break;
	default:
		break;
	}
}