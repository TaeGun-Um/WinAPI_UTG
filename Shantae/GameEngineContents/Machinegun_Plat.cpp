#include "Machinegun_Plat.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Soldier_Aim.h"
#include "Misillie.h"
#include "Machinegun_PlatPiece1.h"
#include "Machinegun_PlatPiece2.h"

#include "Public_Boom.h"
#include "ContentsEnum.h"

Machinegun_Plat::Machinegun_Plat() 
{
}

Machinegun_Plat::~Machinegun_Plat() 
{
}

void Machinegun_Plat::Start()
{
	// Animation
	RenderSet();

	// Collision
	CollisionSet();
}

void Machinegun_Plat::Update(float _DeltaTime)
{
	CollisionCheck();

	if (true == HitAction && 1 == MisillieCount)
	{
		MisillieCount = 0;
		IsCreate = true;
		MisillieCreate();
		AimCreate();
	}

	if (true == MisillieDeath)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Explode_plat.wav");
		BGMPlayer.Volume(0.2f);
		BGMPlayer.LoopCount(1);

		Kill();
	}
}
void Machinegun_Plat::Render(float _DeltaTime)
{
}

void Machinegun_Plat::CollisionCheck()
{
	if (nullptr != MisillieCollision)
	{
		if (true == MisillieCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerEffect), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			HitAction = true;
		}
	}
}

void Machinegun_Plat::MisillieCreate()
{
	Misillie*  NewMisillie = nullptr;
	float4 MisilliePos = float4::Zero;
	MisilliePos = GetPos() + (float4::Down * 950);

	NewMisillie = GetLevel()->CreateActor<Misillie>();
	NewMisillie->SetPos(MisilliePos);
	NewMisillie->SetOwnerPlat(this);
}

void Machinegun_Plat::AimCreate()
{
	NewAim = nullptr;
	float4 AimPos = float4::Zero;
	AimPos = GetPos() + (float4::Up * 25);

	NewAim = GetLevel()->CreateActor<Soldier_Aim>();
	NewAim->SetPos(AimPos);
}

void Machinegun_Plat::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();

	NewAim->SetDeath(true);
	BreakGround();

	ColActor->Death();
}

void Machinegun_Plat::BreakGround()
{
	Machinegun_PlatPiece1* Piece1 = nullptr;
	float4 Piece1Pos = float4::Zero;
	Piece1Pos = GetPos() + (float4::Left * 25);

	Piece1 = GetLevel()->CreateActor<Machinegun_PlatPiece1>();
	Piece1->SetPos(Piece1Pos);
	Piece1->SetOwnerPos(GetPos());

	Machinegun_PlatPiece2* Piece2 = nullptr;
	float4 Piece2Pos = float4::Zero;
	Piece2Pos = GetPos() + (float4::Right * 25);

	Piece2 = GetLevel()->CreateActor<Machinegun_PlatPiece2>();
	Piece2->SetPos(Piece2Pos);
	Piece2->SetOwnerPos(GetPos());
}

void Machinegun_Plat::RenderSet()
{
	AnimationRender = CreateRender("Machinegun_Plat.Bmp", RenderOrder::Map);
	AnimationRender->SetScale({ 100, 50 });
}

void Machinegun_Plat::CollisionSet()
{
	BodyCollision = CreateCollision(CollisionOrder::Ground);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 100, 50 });
	BodyCollision->SetPosition({ 0, 2 });

	MisillieCollision = CreateCollision(CollisionOrder::Trigger);
	MisillieCollision->SetDebugRenderType(CT_Rect);
	MisillieCollision->SetScale({ 5, 500 });
	MisillieCollision->SetPosition({ -50, -250 });
}