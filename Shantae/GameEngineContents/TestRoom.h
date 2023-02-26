#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "MonsterSpawner.h"

class Player;

// Ό³Έν : TestLevel
class TestRoom : public GameEngineLevel
{
public:
	// constrcuter destructer
	TestRoom();
	~TestRoom();

	// delete Function
	TestRoom(const TestRoom& _Other) = delete;
	TestRoom(TestRoom&& _Other) noexcept = delete;
	TestRoom& operator=(const TestRoom& _Other) = delete;
	TestRoom& operator=(TestRoom&& _Other) noexcept = delete;

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

};

