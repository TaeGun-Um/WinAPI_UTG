#include "Soldier_Bullet.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Soldier_Bullet::Soldier_Bullet() 
{
}

Soldier_Bullet::~Soldier_Bullet() 
{
}

void Soldier_Bullet::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });
	AnimationRender->CreateAnimation({ .AnimationName = "Bullet",  .ImageName = "Soldier_Bullet.bmp", .Start = 0, .End = 1, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::MonsterAttack);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 20, 20 });
	BodyCollision->SetPosition({ 1.5f, -2 });
}

void Soldier_Bullet::Update(float _DeltaTime)
{
	AnimationRender->ChangeAnimation("Bullet");
	KillBullet();
	CollisionCheck();
	MoveCalculation(_DeltaTime);
}
void Soldier_Bullet::Render(float _DeltaTime)
{

}

std::string Soldier_Bullet::DirCheck(const std::string_view& _AnimationName)
{
	AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);

	return DirString;
}

// 중력, 점프, 맵타일
void Soldier_Bullet::MoveCalculation(float _DeltaTime)
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

void Soldier_Bullet::CollisionCheck()
{
	// 0202 : 그룹 중 하나라도 충돌했다면 동작
	// GameEngineActor* ColActor = Collision[i]->GetActor();     == 콜리전의 소유 액터를 받아와서 뭔가를 할 수 있음
	// Soldier* FindMonster = Collision[i]->GetOwner<Soldier>(); == 아니면 콜리전의 그룹들을 받아와서 뭔가를 할 수 있음
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			// IsDeath = true;
		}

		if (true == IsDeath)
		{
			GameEngineActor* ColActor = BodyCollision->GetActor();
			ColActor->Off();

			// Explosion();

			ColActor->Death();
		}
	}
}

void Soldier_Bullet::KillBullet()
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

//void Soldier_Bullet::Explosion()
//{
//	Public_Boom* Ex = nullptr;
//	float4 ExPos = float4::Zero;
//	ExPos = GetPos();
//
//	Ex = GetLevel()->CreateActor<Public_Boom>();
//	Ex->SetPos(ExPos);
//}