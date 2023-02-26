#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "MonsterSpawner.h"

class Player;

// Ό³Έν : TestLevel
class TestRoom2 : public GameEngineLevel
{
public:
	// constrcuter destructer
	TestRoom2();
	~TestRoom2();

	// delete Function
	TestRoom2(const TestRoom2& _Other) = delete;
	TestRoom2(TestRoom2&& _Other) noexcept = delete;
	TestRoom2& operator=(const TestRoom2& _Other) = delete;
	TestRoom2& operator=(TestRoom2&& _Other) noexcept = delete;

	GameEngineSoundPlayer BGMPlayer;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	void LevelSet();
	void Debugging();

	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;
	float OverlapTime = 0.0f;
	float DelayTime = 0.2f;

	int Set = 1;
};

