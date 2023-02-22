#include "Soldier_Spider.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Public_Boom.h"
#include "ContentsEnum.h"

Soldier_Spider::Soldier_Spider()
{
}

Soldier_Spider::~Soldier_Spider()
{
}

void Soldier_Spider::Start()
{
	// Animation
	RenderSet();

	// Collision
	CollisionSet();

	ChangeState(Soldier_SpiderState::IDLE);
}

void Soldier_Spider::Update(float _DeltaTime)
{
	CollisionCheck();

	if (1.0f <= AccTime)
	{
		if (1 == ChangeCount)
		{
			ChangeCount = 0;
			ChangeState(Soldier_SpiderState::MOVE);
		}
	}

	if (0 == ChangeCount)
	{
		MoveCalculation(_DeltaTime);

		if (7.0f <= AccTime)
		{
			if (1 == BlinkCount)
			{
				BlinkCount = 0;
				Blinker = true;
			}
			
			//if (true == Blinker)
			//{
			//	AlphaBlinker(_DeltaTime);
			//}

			ChangeState(Soldier_SpiderState::HIT);
		}
	}
}
void Soldier_Spider::Render(float _DeltaTime)
{

}

std::string Soldier_Spider::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;
	AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);

	if (true == MoveDirect)
	{
		DirString = "_L";
	}
	else if (false == MoveDirect)
	{
		DirString = "_R";
	}

	if (PrevDirString != DirString)
	{
		AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);
	}

	return DirString;
}

// 중력, 점프, 맵타일
void Soldier_Spider::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  중력  ///////////////////////////////////////////////////

	if (true == IsGravity)
	{
		MoveDir -= float4::Down * 1500.0f * _DeltaTime;
	}

	if (true == CollisionGround)
	{
		MoveDir.y = 0.0f;
	}

	/////////////////////////////////////////////////// 맵타일 ///////////////////////////////////////////////////

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	//////// RGB(0, 248, 0) ////////
	// 좌우 Turn
	ForwardPosR = GetPos() + (float4::Up * 5) + (float4::Right * 35);
	ForwardPosL = GetPos() + (float4::Up * 5) + (float4::Left * 35);

	if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosR, RGB(0, 0, 0)) && false == MoveDirect)
	{
		MoveSpeed = 0.0f;
		MoveDirect = true;
	}
	else if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosL, RGB(0, 0, 0)) && true == MoveDirect)
	{
		MoveSpeed = 0.0f;
		MoveDirect = false;
	}
	else
	{
		MoveSpeed = 300.0f;
	}

	/////////////////////////////////////////////////// 기타 조건 ///////////////////////////////////////////////////

	//////// 최종 위치 ////////

	UpdateState(_DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void Soldier_Spider::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Ground), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			CollisionGround = true;
		}
	}
	if (nullptr != SensorCollision)
	{
		if (true == SensorCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			if (0 == ChangeCount)
			{
				IsAttack = true;
			}
		}
	}
}

void Soldier_Spider::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();

	// Explosion();

	ColActor->Death();
}

void Soldier_Spider::Explosion()
{
	Public_Boom* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos() + (float4::Up * 60);

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(ExPos);
	Ex->SetExPlus(1);
}

void Soldier_Spider::AlphaBlinker(float _DeltaTime)
{
	BlinkTime += _DeltaTime;

	if (true == Blinker)
	{
		if (0.15f <= BlinkTime)
		{
			BlinkTime = 0.0f;
			Blinker = false;
			AnimationRender->SetAlpha(255);
		}
		if (0.10f <= BlinkTime && true == Blinker)
		{
			AnimationRender->SetAlpha(120);
		}
		else if (0.05f <= BlinkTime && true == Blinker)
		{
			AnimationRender->SetAlpha(180);
		}
		else if (0.05f >= BlinkTime && true == Blinker)
		{
			AnimationRender->SetAlpha(240);
		}
	}
}

void Soldier_Spider::RenderSet()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Soldier_Spider_R.bmp", .Start = 0, .End = 5, .InterTime = 0.05f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Spider_R.bmp", .Start = 6, .End = 11, .InterTime = 0.05f });
	AnimationRender->CreateAnimation({ .AnimationName = "Attack_R",  .ImageName = "Soldier_Spider_R.bmp", .Start = 12, .End = 16, .InterTime = 0.12f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hit_R",  .ImageName = "Soldier_Spider_R.bmp", .Start = 17, .End = 17, .InterTime = 0.5f, .Loop = false });

	// Left
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Soldier_Spider_L.bmp", .Start = 0, .End = 5, .InterTime = 0.05f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_L",  .ImageName = "Soldier_Spider_L.bmp", .Start = 6, .End = 11, .InterTime = 0.05f });
	AnimationRender->CreateAnimation({ .AnimationName = "Attack_L",  .ImageName = "Soldier_Spider_L.bmp", .Start = 12, .End = 16, .InterTime = 0.12f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hit_L",  .ImageName = "Soldier_Spider_L.bmp", .Start = 17, .End = 17, .InterTime = 0.5f, .Loop = false });

}
void Soldier_Spider::CollisionSet()
{
	BodyCollision = CreateCollision(CollisionOrder::Effect);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 50 });
	BodyCollision->SetPosition({ 0, 0 });

	AttackCollision = CreateCollision(CollisionOrder::MonsterAttack);
	AttackCollision->SetDebugRenderType(CT_Rect);
	AttackCollision->SetScale({ 10, 100 });
	AttackCollision->SetPosition({ 0, -50 });
	AttackCollision->Off();

	SensorCollision = CreateCollision(CollisionOrder::Trigger);
	SensorCollision->SetDebugRenderType(CT_Rect);
	SensorCollision->SetScale({ 10, 150 });
	SensorCollision->SetPosition({ 0, -100 });
}