#include "Misillie.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "Public_Boom.h"
#include "Machinegun_Plat.h"

Misillie::Misillie() 
{
}

Misillie::~Misillie() 
{
}

void Misillie::Start()
{
	// Animation
	AnimationRender = CreateRender("Misillie.Bmp", RenderOrder::Effect);
	AnimationRender->SetScale({ 400, 400 });
	
	// Collision
	BodyCollision = CreateCollision(CollisionOrder::Effect);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 75 });
	BodyCollision->SetPosition({ 0, 0 });
}

void Misillie::Update(float _DeltaTime)
{
	CollisionCheck();
	MoveCalculation(_DeltaTime);
}
void Misillie::Render(float _DeltaTime)
{

}

// 중력, 점프, 맵타일
void Misillie::MoveCalculation(float _DeltaTime)
{
	MoveSpeed = 900.0f;
	SetMove(float4::Up * MoveSpeed * _DeltaTime);
}

void Misillie::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Ground), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			IsDeath = true;
			OwnerPlat->IsMisillieDeath(IsDeath);
			Kill();
		}
	}
}

void Misillie::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();

	Explosion();

	ColActor->Death();
}

void Misillie::Explosion()
{
	Public_Boom* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos() + (float4::Up * 30);

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(ExPos);
	Ex->SetExPlus(0);
	Ex->SetSoundOff();
}