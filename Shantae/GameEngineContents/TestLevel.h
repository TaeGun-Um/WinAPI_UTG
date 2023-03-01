#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "MonsterSpawner.h"

class Player;
class GameEngineTileMap;

// Ό³Έν : TestLevel
class TestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TestLevel();
	~TestLevel();

	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

	GameEngineSoundPlayer BGMPlayer;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	void LevelSet();
	void Debugging();
	void CameraAction();
	void Portal();

	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;
	float OverlapTime = 0.0f;
	float DelayTime = 0.2f;

	int Set = 1;
	
	// MonsterSpawner* CreateSpawner(const float4& _SpawnerPos, const std::string_view& _MonsterType, GameEngineImage* _MonsterColMap, const float4& _MonstorPos);
	
};

