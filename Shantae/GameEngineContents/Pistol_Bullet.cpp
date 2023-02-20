#include "Pistol_Bullet.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Pistol_Bullet::Pistol_Bullet() 
{
}

Pistol_Bullet::~Pistol_Bullet() 
{
}

void Pistol_Bullet::Start()
{
	AnimationRender = CreateRender(RenderOrder::Player);
	AnimationRender->SetScale({ 400, 400 });
	AnimationRender->CreateAnimation({ .AnimationName = "Bullet",  .ImageName = "Pistol_Bullet.bmp", .Start = 0, .End = 2, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Bulletmark",  .ImageName = "Pistol_Bullet.bmp", .Start = 3, .End = 5, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::PlayerPistolAttack);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 20, 20 });
	BodyCollision->SetPosition({ 1.5f, -2 });
}

void Pistol_Bullet::Update(float _DeltaTime)
{
	AnimationRender->ChangeAnimation("Bullet");
	KillBullet();
	CollisionCheck();
	MoveCalculation(_DeltaTime);
}
void Pistol_Bullet::Render(float _DeltaTime)
{

}

std::string Pistol_Bullet::DirCheck(const std::string_view& _AnimationName)
{
	AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);

	return DirString;
}

// 중력, 점프, 맵타일
void Pistol_Bullet::MoveCalculation(float _DeltaTime)
{
	if ("_L" == DirString)
	{
		SetMove(float4::Left * 600.0f * _DeltaTime);
	}
	else
	{
		SetMove(float4::Right * 600.0f * _DeltaTime);
	}

	/////////////////////////////////////////////////// 맵타일 ///////////////////////////////////////////////////

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	// 땅
	float4 Land = GetPos() + (float4::Down * 20);
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(Land, RGB(0, 0, 0)))
	{
		IsDeath = true;
		MoveDir.y = 0.0f;
	}
	if (RGB(74, 65, 42) == ColMap->GetPixelColor(Land, RGB(0, 0, 0)))
	{
		IsDeath = true;
		MoveDir.y = 0.0f;
	}

	/////////////////////////////////////////////////// 기타 조건 ///////////////////////////////////////////////////

	//////// 최종 위치 ////////

	SetMove(MoveDir * _DeltaTime);
}

void Pistol_Bullet::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			AnimationRender->ChangeAnimation("Bulletmark");
			IsDeath = true;
		}

		if (true == IsDeath)
		{
			GameEngineActor* ColActor = BodyCollision->GetActor();
			ColActor->Off();

			ColActor->Death();
		}
	}
}

void Pistol_Bullet::KillBullet()
{
	float4 RPos = OwnerPos + (float4::Right * 1000);
	float4 LPos = OwnerPos + (float4::Left * 1000);

	if ("_L" == DirString)
	{
		if (GetPos().x <= LPos.x)
		{
			IsDeath = true;
		}
	}
	else
	{
		if (GetPos().x >= RPos.x)
		{
			IsDeath = true;
		}
	}
}