#include "Soldier_Bomberman.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

#include "Public_Boom.h"
#include "Soldier_Boom.h"
#include "Player.h"
#include "DamageText.h"

#include "Gem.h"
#include "Heart.h"

Soldier_Bomberman::Soldier_Bomberman()
{
}

Soldier_Bomberman::~Soldier_Bomberman()
{
}

void Soldier_Bomberman::Start()
{
	// Animation
	RenderSet();

	// Collision
	CollisionSet();

	// Text(예시; 0206 추가)
	//GameEngineRender* Render = CreateRender(RenderOrder::Monster);
	//Render->SetText("1234");

	// state
	ChangeState(Soldier_BombermanState::CROUCH);
}

void Soldier_Bomberman::Update(float _DeltaTime)
{
	CharacterDirectSetting(_DeltaTime);
	CollisionCheck();
	MoveCalculation(_DeltaTime);

	if (true == Blinker)
	{
		AlphaBlinker(_DeltaTime);
	}
}

void Soldier_Bomberman::Render(float _DeltaTime)
{

}

void Soldier_Bomberman::CharacterDirectSetting(float _DeltaTime)
{
	float interval = Player::MainPlayer->GetPos().x - GetPos().x;
		
	if (true == trace)
	{
		if (0.0f >= interval)
		{
			MoveDirect = true;
		}
		else
		{
			MoveDirect = false;
		}
	}
}

std::string Soldier_Bomberman::DirCheck(const std::string_view& _AnimationName)
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
void Soldier_Bomberman::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  중력  ///////////////////////////////////////////////////

	if (true == IsGravity && MoveDir.y <= 1800)
	{
		MoveDir += float4::Down * 1500.0f * _DeltaTime;
	}

	/////////////////////////////////////////////////// 맵타일 ///////////////////////////////////////////////////

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	//////// RGB(0, 248, 0) ////////
	// 땅
	NextPos = GetPos() + MoveDir * _DeltaTime;
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		if (false == HitAction)
		{
			MoveDir.y = 0.0f;
		}
	}

	//////// RGB(74, 65, 42) ////////
	// 땅
	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		if (false == HitAction)
		{
			MoveDir.y = 0.0f;
		}
	}

	/////////////////////////////////////////////////// 기타 조건 ///////////////////////////////////////////////////

	//////// 최종 위치 ////////

	UpdateState(_DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void Soldier_Bomberman::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Strike_enemy.mp3");
			BGMPlayer.Volume(0.075f);
			BGMPlayer.LoopCount(1);

			CreateText();

			HitAction = true;
			Blinker = true;
		}

		if (true == IsDeath)
		{
			Kill();
		}
	}
}

void Soldier_Bomberman::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();

	Explosion();
	CreateItem();

	ColActor->Death();
}

void Soldier_Bomberman::Throw()
{
	BoomCount = 0;

	Soldier_Boom* NewBooms = nullptr;
	float4 BoomPos = float4::Zero;
	BoomPos = GetPos() + (float4::Up * 90);

	NewBooms = GetLevel()->CreateActor<Soldier_Boom>();
	NewBooms->SetColMap(ColMap);
	NewBooms->SetPos(BoomPos);
	NewBooms->SetDir(DirString);
}

void Soldier_Bomberman::Explosion()
{
	Public_Boom* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos() + (float4::Up * 60);

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(ExPos);
	Ex->SetExPlus(1);
}

void Soldier_Bomberman::AlphaBlinker(float _DeltaTime)
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

void Soldier_Bomberman::RenderSet()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Crouch_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 19, .End = 24, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Lob_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 25, .End = 34, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hit_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 41, .End = 41, .InterTime = 0.5f, .Loop = false });

	// Left
	AnimationRender->CreateAnimation({ .AnimationName = "Crouch_L",  .ImageName = "Soldier_Blue_L.bmp", .Start = 19, .End = 24, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Lob_L",  .ImageName = "Soldier_Blue_L.bmp", .Start = 25, .End = 34, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hit_L",  .ImageName = "Soldier_Blue_L.bmp", .Start = 41, .End = 41, .InterTime = 0.5f, .Loop = false });
}
void Soldier_Bomberman::CollisionSet()
{
	BodyCollision = CreateCollision(CollisionOrder::Monster);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 100, 110 });
	BodyCollision->SetPosition({ 0, -55 });
}

void Soldier_Bomberman::CreateItem()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 3);

	if (1 == RandC)
	{
		Gem* Gems = nullptr;

		Gems = GetLevel()->CreateActor<Gem>();
		Gems->SetPos(GetPos());
		Gems->SetColMap(ColMap);
		Gems->SetJarSize("small");
	}
}

void Soldier_Bomberman::CreateText()
{
	DamageText* NewT = nullptr;
	float4 NewTPos = float4::Zero;

	NewT = GetLevel()->CreateActor<DamageText>();
	NewT->SetPos(GetPos() + float4::Up * 140 + float4::Left * 20);
}