#include "Boss_Boom_Red.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Public_Boom.h"
#include "SmallPoof.h"

Boss_Boom_Red::Boss_Boom_Red()
{
}

Boss_Boom_Red::~Boss_Boom_Red()
{
}

void Boss_Boom_Red::Start()
{
	// Animation
	AnimationRender = CreateRender("Boom_Red.Bmp", RenderOrder::Effect);
	AnimationRender->SetScale({ 100, 100 });

	// Collision
	BodyCollision = CreateCollision(CollisionOrder::MonsterAttack);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 50 });
}

void Boss_Boom_Red::Update(float _DeltaTime)
{
	//DirectCheckForKill();
	CollisionCheck();
	if (false == ChangeDir)
	{
		MoveCalculation(_DeltaTime);
	}
	if (true == ChangeDir)
	{
		Change(_DeltaTime);
	}
}
void Boss_Boom_Red::Render(float _DeltaTime)
{

}

// 중력, 점프, 맵타일
void Boss_Boom_Red::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  이동  ///////////////////////////////////////////////////

	MoveDir += float4::Down * 3000.0f * _DeltaTime;

	SetMove(float4::Left * MoveSpeed * _DeltaTime);

	/////////////////////////////////////////////////// 맵타일 ///////////////////////////////////////////////////

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	// 땅
	float4 Land = GetPos() + (float4::Down * 20);
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(Land, RGB(0, 248, 0)))
	{
		MoveDir.y = 0.0f;
		Bounce();
	}
	if (RGB(74, 65, 42) == ColMap->GetPixelColor(Land, RGB(74, 65, 42)))
	{
		MoveDir.y = 0.0f;
		Bounce();
	}

	/////////////////////////////////////////////////// 기타 조건 ///////////////////////////////////////////////////

	//////// 최종 위치 ////////

	SetMove(MoveDir * _DeltaTime);
}

void Boss_Boom_Red::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Effect), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			Kill();
		}
	}

	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			AttackCollision = CreateCollision(CollisionOrder::Trigger);
			AttackCollision->SetDebugRenderType(CT_Rect);
			AttackCollision->SetScale({ 50, 50 });
			ChangeDir = true;
		}
	}

	if (nullptr != AttackCollision)
	{
		if (true == AttackCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			Kill();
		}
	}
}

void Boss_Boom_Red::Bounce()
{
	MoveSpeed = 300.0f;
	MoveDir.y -= 1300.0f;
	CreatePoof();
}

void Boss_Boom_Red::Change(float _DeltaTime)
{
	MoveSpeed = 2000.0f;
	SetMove(float4::Right * MoveSpeed * _DeltaTime);
}

void Boss_Boom_Red::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	BodyCollision->Off();
	ColActor->Off();

	Explosion();

	ColActor->Death();
}

void Boss_Boom_Red::DirectCheckForKill()
{
	float4 Pos = OwnerPos + (float4::Left * 1500);

	if (GetPos().x <= Pos.x)
	{
		Kill();
	}
}

void Boss_Boom_Red::Explosion()
{
	Public_Boom* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos();

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(ExPos);
}

void Boss_Boom_Red::CreatePoof()
{
	SmallPoof* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos() + (float4::Up * 20);

	Ex = GetLevel()->CreateActor<SmallPoof>();
	Ex->SetPos(ExPos);
}