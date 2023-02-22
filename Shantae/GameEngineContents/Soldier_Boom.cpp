#include "Soldier_Boom.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>

#include "Public_Boom.h"
#include "ContentsEnum.h"

Soldier_Boom::Soldier_Boom() 
{
}

Soldier_Boom::~Soldier_Boom() 
{
}

void Soldier_Boom::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });
	AnimationRender->CreateAnimation({ .AnimationName = "Boom_R",  .ImageName = "Soldier_Boom_R.bmp", .Start = 0, .End = 11, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Boom_L",  .ImageName = "Soldier_Boom_L.bmp", .Start = 0, .End = 11, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::MonsterAttack);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 50 });
	BodyCollision->SetPosition({ 5, 0 });
}

void Soldier_Boom::Update(float _DeltaTime)
{
	if (1 == BoomThrowSound)
	{
		BoomThrowSound = 0;
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Soldier_boom_throw.mp3");
		BGMPlayer.Volume(0.05f);
		BGMPlayer.LoopCount(1);
	}

	DirCheck("Boom");
	CollisionCheck();
	MoveCalculation(_DeltaTime);
}
void Soldier_Boom::Render(float _DeltaTime)
{

}

std::string Soldier_Boom::DirCheck(const std::string_view& _AnimationName)
{
	AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);

	return DirString;
}

// �߷�, ����, ��Ÿ��
void Soldier_Boom::MoveCalculation(float _DeltaTime)
{
	if ("_L" == DirString)
	{
		SetMove(float4::Left * 450.0f *_DeltaTime);
	}
	else
	{
		SetMove(float4::Right * 450.0f * _DeltaTime);
	}

	///////////////////////////////////////////////////  �߷�  ///////////////////////////////////////////////////

	if (true == IsStart)
	{
		IsStart = false;
		MoveDir.y += -1000.0f;
		SetMove(MoveDir * _DeltaTime);
	}
	
	MoveDir += float4::Down * 3000.0f * _DeltaTime;

	/////////////////////////////////////////////////// ��Ÿ�� ///////////////////////////////////////////////////

	if (nullptr == ColMap)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}

	// ��
	float4 Land = GetPos() + (float4::Down * 20);
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(Land, RGB(0, 248, 0)))
	{
		MoveDir.y = 0.0f;
		Kill();
	}
	if (RGB(74, 65, 42) == ColMap->GetPixelColor(Land, RGB(74, 65, 42)))
	{
		MoveDir.y = 0.0f;
		Kill();
	}

	/////////////////////////////////////////////////// ��Ÿ ���� ///////////////////////////////////////////////////

	//////// ���� ��ġ ////////
	
	SetMove(MoveDir * _DeltaTime);
}

void Soldier_Boom::CollisionCheck()
{
	// 0202 : �׷� �� �ϳ��� �浹�ߴٸ� ����
	// GameEngineActor* ColActor = Collision[i]->GetActor();     == �ݸ����� ���� ���͸� �޾ƿͼ� ������ �� �� ����
	// Soldier* FindMonster = Collision[i]->GetOwner<Soldier>(); == �ƴϸ� �ݸ����� �׷���� �޾ƿͼ� ������ �� �� ����
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Effect), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			Kill();
		}
	}
}

void Soldier_Boom::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	BodyCollision->Off();
	ColActor->Off();

	Explosion();

	ColActor->Death();
}

void Soldier_Boom::Explosion()
{
	Public_Boom* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos();

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(ExPos);
}