#include "Boss_Boom.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>

#include "Public_Boom.h"
#include "ContentsEnum.h"

Boss_Boom::Boss_Boom() 
{
}

Boss_Boom::~Boss_Boom() 
{
}

void Boss_Boom::Start()
{
	// Animation
	AnimationRender = CreateRender("Boom_Black.Bmp", RenderOrder::Effect);
	AnimationRender->SetScale({ 100, 100 });

	// Collision
	BodyCollision = CreateCollision(CollisionOrder::MonsterAttack);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 50 });
}

void Boss_Boom::Update(float _DeltaTime)
{
	DirectCheckForKill();
	CollisionCheck();
	MoveCalculation(_DeltaTime);
}
void Boss_Boom::Render(float _DeltaTime)
{

}

// 중력, 점프, 맵타일
void Boss_Boom::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  이동  ///////////////////////////////////////////////////

	MoveDir += float4::Down * 1500.0f * _DeltaTime;

	SetMove(float4::Left * 1450.0f * _DeltaTime);

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

void Boss_Boom::CollisionCheck()
{
	// 0202 : 그룹 중 하나라도 충돌했다면 동작
	// GameEngineActor* ColActor = Collision[i]->GetActor();     == 콜리전의 소유 액터를 받아와서 뭔가를 할 수 있음
	// Soldier* FindMonster = Collision[i]->GetOwner<Soldier>(); == 아니면 콜리전의 그룹들을 받아와서 뭔가를 할 수 있음
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Effect), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			Kill();
		}
	}
}

void Boss_Boom::Bounce()
{
	MoveDir.y += -1000.0f;
}

void Boss_Boom::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	BodyCollision->Off();
	ColActor->Off();

	Explosion();

	ColActor->Death();
}

void Boss_Boom::DirectCheckForKill()
{
	float4 Pos = OwnerPos + (float4::Left * 1500);

	if (GetPos().x <= Pos.x)
	{
		Kill();
	}
}

void Boss_Boom::Explosion()
{
	Public_Boom* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos();

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(ExPos);
}