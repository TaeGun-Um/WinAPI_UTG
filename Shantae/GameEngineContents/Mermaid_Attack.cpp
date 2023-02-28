#include "Mermaid_Attack.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Mermaid_AttackBoom.h"

Mermaid_Attack::Mermaid_Attack() 
{
}

Mermaid_Attack::~Mermaid_Attack() 
{
}

void Mermaid_Attack::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Mermaid_Attack",  .ImageName = "Mermaid_Attack.bmp", .Start = 0, .End = 3, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::MonsterAttack);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 20, 20 });
	BodyCollision->SetPosition({ 1.5f, -2 });

	AnimationRender->ChangeAnimation("Mermaid_Attack");
}

void Mermaid_Attack::Update(float _DeltaTime)
{
	KillBullet();
	CollisionCheck();
	MoveCalculation(_DeltaTime);
}

void Mermaid_Attack::Render(float _DeltaTime)
{

}

std::string Mermaid_Attack::DirCheck(const std::string_view& _AnimationName)
{
	AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);

	return DirString;
}

// 중력, 점프, 맵타일
void Mermaid_Attack::MoveCalculation(float _DeltaTime)
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

void Mermaid_Attack::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Effect), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			IsDeath = true;
		}

		if (true == IsDeath)
		{
			GameEngineActor* ColActor = BodyCollision->GetActor();
			ColActor->Off();

			Explosion();

			ColActor->Death();
		}
	}
}

void Mermaid_Attack::KillBullet()
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

void Mermaid_Attack::Explosion()
{
	Mermaid_AttackBoom* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos();

	Ex = GetLevel()->CreateActor<Mermaid_AttackBoom>();
	Ex->SetPos(ExPos);
}