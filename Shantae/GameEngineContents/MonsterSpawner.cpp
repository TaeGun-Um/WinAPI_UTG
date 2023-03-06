#include "MonsterSpawner.h"

#include <GameEnginePlatform/GameEngineInput.h>
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

	// Text(예시; 0206 추가)
	SpawnerText.resize(4);
	BoxScale = { 200, 150 };

	SpawnerText[0] = "오류1";
	SpawnerText[1] = "오류2";
	SpawnerText[2] = "오류3";
	SpawnerText[3] = "오류3";

	TextRender1 = CreateRender(RenderOrder::UI);
	TextRender2 = CreateRender(RenderOrder::UI);
	TextRender3 = CreateRender(RenderOrder::UI);
	TextRender4 = CreateRender(RenderOrder::UI);

	TextRender1->SetText(SpawnerText[0], 20, "굴림", TextAlign::Left, RGB(0, 0, 0), BoxScale);
	TextRender2->SetText(SpawnerText[1], 20, "굴림", TextAlign::Left, RGB(255, 0, 255), BoxScale);
	TextRender3->SetText(SpawnerText[2], 20, "굴림", TextAlign::Left, RGB(0, 0, 0), BoxScale);
	TextRender4->SetText(SpawnerText[3], 20, "굴림", TextAlign::Left, RGB(0, 0, 0), BoxScale);
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

	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		IsText = !IsText;
	}

	if (true == IsText)
	{
		TextRender1->On();
		TextRender2->On();
		TextRender3->On();
		PositionText();
	}
	else
	{
		TextRender1->Off();
		TextRender2->Off();
		TextRender3->Off();
	}
}

void MonsterSpawner::SpawnerSetting(const std::string_view& _Type, GameEngineImage* _ColMap, const float4 _Value, float _Time)
{
	std::string UpperName = GameEngineString::ToUpper(_Type);

	if (GameEngineString::ToUpper("Blue") == UpperName)
	{
		IsBlue = true;
		MonsterTYPE = "Blue";
	}
	else if (GameEngineString::ToUpper("Bomberman") == UpperName)
	{
		IsBomberman = true;
		MonsterTYPE = "Bomberman";
	}
	else if (GameEngineString::ToUpper("Red") == UpperName)
	{
		IsRed = true;
		MonsterTYPE = "Red";
	}
	else if (GameEngineString::ToUpper("Black") == UpperName)
	{
		IsBlack = true;
		MonsterTYPE = "Black";
	}
	else if (GameEngineString::ToUpper("Spider") == UpperName)
	{
		IsSpider = true;
		MonsterTYPE = "Spider";
	}
	else
	{
		MsgAssert("올바른 몬스터 종류를 넣어주세요." + UpperName);
		return;
	}

	MonsterColMap = _ColMap;
	MonsterPos = _Value;
	SpawnTime = _Time;
}

void MonsterSpawner::CollisionCheck()
{
	if (nullptr != SpawnSpot)
	{
		if (true == SpawnSpot->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerEffect), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
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
					MsgAssert("Spawner의 bool값이 정상적으로 입력되지 못했습니다.");
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

void MonsterSpawner::PositionText()
{
	std::string MonsterType = MonsterTYPE;
	std::string Timer = std::to_string(AccTime);
	std::string PossibleTime = std::to_string(SpawnTime);
	std::string MonsterPosision = MonsterPos.ToString();

	SpawnerText[0] = MonsterType;
	SpawnerText[1] = Timer;
	SpawnerText[2] = PossibleTime;
	SpawnerText[3] = MonsterPosision;

	TextRender1->SetText(SpawnerText[0], 20, "굴림", TextAlign::Left, RGB(0, 255, 0), BoxScale);
	TextRender1->SetPosition(float4::Down * 540 + float4::Right * 50);

	TextRender2->SetText(SpawnerText[1], 20, "굴림", TextAlign::Left, RGB(255, 0, 0), BoxScale);
	TextRender2->SetPosition(float4::Down * 520 + float4::Right * 50);

	TextRender3->SetText(SpawnerText[2], 20, "굴림", TextAlign::Left, RGB(0, 255, 0), BoxScale);
	TextRender3->SetPosition(float4::Down * 500 + float4::Right * 50);

	TextRender4->SetText(SpawnerText[3], 15, "굴림", TextAlign::Left, RGB(0, 255, 0), BoxScale);
	TextRender4->SetPosition(float4::Down * 560 + float4::Right * 50);
}