#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;

// Ό³Έν : FieldLevel_1
class House : public PlayLevel
{
public:
	// constrcuter destructer
	House();
	~House();

	// delete Function
	House(const House& _Other) = delete;
	House(House&& _Other) noexcept = delete;
	House& operator=(const House& _Other) = delete;
	House& operator=(House&& _Other) noexcept = delete;

protected:
	void Loading();
	void Update(float _DeltaTime);

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	void LevelSet();
	void Debugging();
	void AnimationChange(float _DeltaTime);
	void SoundCombination(float _DeltaTime);

	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;

	GameEngineSoundPlayer BGMPlayer;

	float OverlapTime = 0.0f;
	float AnimationTime = 0.0f;
	float SeagullTime = 0.0f;
	float WaveTime = 1;
	float BellTime = 1;

	int Set = 1;
	int Change = 0;
	int SeagullCount = 1;
	int WaveCount = 1;
	int BellCount = 1;

	int ExplosionCount = 1;

	int AnimationChangeCount1 = 1;
	int AnimationChangeCount2 = 1;
	int AnimationChangeCount3 = 1;
	int AnimationChangeCount4 = 1;

	int Ani1 = 1;
	int Ani2 = 1;
	int Ani3 = 1;

};

