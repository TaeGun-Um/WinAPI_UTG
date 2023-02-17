#include "MonsterSpawner.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

#include "Player.h"

#include "Soldier_Blue.h"
#include "Soldier_Black.h"
#include "Soldier_Red.h"
#include "Soldier_Bomberman.h"
#include "Soldier_Spider.h"

MonsterSpawner::MonsterSpawner() 
{
}

MonsterSpawner::~MonsterSpawner() 
{
}

void MonsterSpawner::Start()
{
	// Collision
	SpawnSpot = CreateCollision(CollisionOrder::Spawner);
	SpawnSpot->SetDebugRenderType(CT_Rect);
	SpawnSpot->SetScale({ 50, GameEngineWindow::GetScreenSize().y});
	SpawnSpot->SetPosition({ 0, GameEngineWindow::GetScreenSize().hy()});

	// Text(����; 0206 �߰�)
	TextRender = CreateRender(RenderOrder::Monster);
	TextRender->SetText("Spawner");
}

void MonsterSpawner::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (SpawnTime <= AccTime)
	{
		Spawncount = 1;
	}
	else
	{
		Spawncount = 0;
	}

	CollisionCheck();
}

void MonsterSpawner::SpawnerSetting(const std::string_view& _Type, GameEngineImage* _ColMap, const float4 _Value, float _Time)
{
	std::string UpperName = GameEngineString::ToUpper(_Type);

	if (GameEngineString::ToUpper("Blue") == UpperName)
	{
		IsBlue = true;
	}
	else if (GameEngineString::ToUpper("Bomberman") == UpperName)
	{
		IsBomberman = true;
	}
	else if (GameEngineString::ToUpper("Red") == UpperName)
	{
		IsRed = true;
	}
	else if (GameEngineString::ToUpper("Black") == UpperName)
	{
		IsBlack = true;
	}
	else if (GameEngineString::ToUpper("Spider") == UpperName)
	{
		IsSpider = true;
	}
	else
	{
		MsgAssert("�ùٸ� ���� ������ �־��ּ���." + UpperName);
		return;
	}

	MonsterColMap = _ColMap;
	MonsterPos = _Value;
	SpawnTime = _Time;
}

void MonsterSpawner::CollisionCheck()
{
	// 0202 : �׷� �� �ϳ��� �浹�ߴٸ� ����
	// GameEngineActor* ColActor = Collision[i]->GetActor();     == �ݸ����� ���� ���͸� �޾ƿͼ� ������ �� �� ����
	// Soldier* FindMonster = Collision[i]->GetOwner<Soldier>(); == �ƴϸ� �ݸ����� �׷���� �޾ƿͼ� ������ �� �� ����

	if (nullptr != SpawnSpot)
	{
		if (true == SpawnSpot->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			if (1 == Spawncount)
			{
				if (true == IsBlue)
				{
					AccTime = 0.0f;
					BlueSpawn();
				}
				else if (true == IsBomberman)
				{
					AccTime = 0.0f;
					BombermanSpawn();
				}
				else if (true == IsRed)
				{
					AccTime = 0.0f;
					RedSpawn();
				}
				else if (true == IsBlack)
				{
					AccTime = 0.0f;
					BlackSpawn();
				}
				else if (true == IsSpider)
				{
					AccTime = 0.0f;
					SpiderSpawn();
				}
				else
				{
					MsgAssert("Spawner�� bool���� ���������� �Էµ��� ���߽��ϴ�.");
					return;
				}
			}
		}
	}
}

void MonsterSpawner::BlueSpawn()
{
	GameEngineActor* SpawnActor = GetLevel()->CreateActor<Soldier_Blue>();
	Soldier_Blue* SPW = dynamic_cast<Soldier_Blue*>(SpawnActor);

	SpawnActor->SetPos(MonsterPos);
	SPW->SetColMap(MonsterColMap);
	if (true == IsAmbush)
	{
		SPW->SetAmbushTrue();
	}
}

void MonsterSpawner::RedSpawn()
{
	GameEngineActor* SpawnActor = GetLevel()->CreateActor<Soldier_Red>();
	Soldier_Red* SPW = dynamic_cast<Soldier_Red*>(SpawnActor);

	SpawnActor->SetPos(MonsterPos);
	SPW->SetColMap(MonsterColMap);
	if (true == IsAmbush)
	{
		SPW->SetAmbushTrue();
	}
}

void MonsterSpawner::BlackSpawn()
{
	GameEngineActor* SpawnActor = GetLevel()->CreateActor<Soldier_Black>();
	Soldier_Black* SPW = dynamic_cast<Soldier_Black*>(SpawnActor);

	SpawnActor->SetPos(MonsterPos);
	SPW->SetColMap(MonsterColMap);
}

void MonsterSpawner::SpiderSpawn()
{
	GameEngineActor* SpawnActor = GetLevel()->CreateActor<Soldier_Spider>();
	Soldier_Spider* SPW = dynamic_cast<Soldier_Spider*>(SpawnActor);

	SpawnActor->SetPos(MonsterPos);
	SPW->SetColMap(MonsterColMap);
}

void MonsterSpawner::BombermanSpawn()
{
	GameEngineActor* SpawnActor = GetLevel()->CreateActor<Soldier_Bomberman>();
	Soldier_Bomberman* SPW = dynamic_cast<Soldier_Bomberman*>(SpawnActor);

	SpawnActor->SetPos(MonsterPos);
	SPW->SetColMap(MonsterColMap);
}