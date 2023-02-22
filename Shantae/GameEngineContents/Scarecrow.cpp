#include "Scarecrow.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Scarecrow::Scarecrow() 
{
}

Scarecrow::~Scarecrow() 
{
}

// 더미 몬스터
void Scarecrow::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Scarecrow_R.bmp", .Start = 0, .End = 6, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Scarecrow_L.bmp", .Start = 0, .End = 6, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::Monster);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 90 });
	BodyCollision->SetPosition({ 0, -50 });

	AnimationRender->ChangeAnimation("Idle_L");
}

void Scarecrow::Update(float _DeltaTime)
{
	CollisionCheck(_DeltaTime);
	MoveCalculation(_DeltaTime);

	if (true == Blinker)
	{
		AlphaBlinker(_DeltaTime);
	}

	if (true == CreateT)
	{
		TextPos = DamageText->GetPosition();
	}
}
void Scarecrow::Render(float _DeltaTime)
{

}

void Scarecrow::MoveCalculation(float _DeltaTime)
{
	MoveDir += float4::Down * 1500.0f * _DeltaTime;

	// 땅
	NextPos = GetPos() + MoveDir * _DeltaTime;
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir.y = 0.0f;
	}

	//////// RGB(74, 65, 42) ////////
	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir.y = 0.0f;

		while (RGB(74, 65, 42) == ColMap->GetPixelColor(GetPos(), RGB(0, 0, 0)))
		{
			MoveDir.y -= 1.0f;
			SetMove(MoveDir);
			if (RGB(74, 65, 42) != ColMap->GetPixelColor(GetPos(), RGB(0, 0, 0)))
			{
				break;
			}
		}
	}

	SetMove(MoveDir * _DeltaTime);
}

void Scarecrow::CollisionCheck(float _DeltaTime)
{
	//std::string MouseText = "MousePosition : \n";
	//MouseText += GetLevel()->GetMousePos().ToString();

	//std::string CameraMouseText = "MousePositionCamera : ";
	//CameraMouseText += GetLevel()->GetMousePosToCamera().ToString();

	//GameEngineLevel::DebugTextPush(MouseText);
	//// GameEngineLevel::DebugTextPush(CameraMouseText);

	////std::string Text = "출력";
	////SetBkMode(DoubleDC, TRANSPARENT);
	////TextOut(DoubleDC, 0, 0, Text.c_str(), Text.size());

	//// 디버깅용.

	HitTime += _DeltaTime;

	if (0.2f <= HitTime)
	{
		Hitonoff = true;
		BodyCollision->On();
	}

	if (nullptr != BodyCollision)
	{
		if (true == Hitonoff)
		{
			if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
			{
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Strike_enemy.mp3");
				BGMPlayer.Volume(0.05f);
				BGMPlayer.LoopCount(1);

				Hitonoff = false;
				HitTime = 0.0f;
				BodyCollision->Off();
				Blinker = true;
				CreateText();
			}
		}
	}
}

void Scarecrow::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();
	ColActor->Death();
}

void Scarecrow::CreateText()
{
	CreateT = true;
	DamageText = CreateRender(RenderOrder::UI);
	DamageText->SetText("-5");
	DamageText->SetPosition(GetPos());
}

void Scarecrow::AlphaBlinker(float _DeltaTime)
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