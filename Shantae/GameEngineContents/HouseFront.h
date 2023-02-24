#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class BlackBox;

// Ό³Έν : FieldLevel_2
class HouseFront : public PlayLevel
{
public:
	// constrcuter destructer
	HouseFront();
	~HouseFront();

	// delete Function
	HouseFront(const HouseFront& _Other) = delete;
	HouseFront(HouseFront&& _Other) noexcept = delete;
	HouseFront& operator=(const HouseFront& _Other) = delete;
	HouseFront& operator=(HouseFront&& _Other) noexcept = delete;

protected:
	void Loading();
	void Update(float _DeltaTime);

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	void BlackBoxOutAnimation();
	void BlackBoxInAnimation();
	void InBoxKill();

	BlackBox* BBoxOut = nullptr;
	BlackBox* BBoxIn = nullptr;
	int BBoxOutCount = 1;
	int BBoxInCount = 1;

	void LevelSet();
	void Debugging();
	void SoundCombination(float _DeltaTime);

	GameEngineSoundPlayer BGMPlayer;
	GameEngineSoundPlayer SeagullPlayer;
	GameEngineSoundPlayer WavePlayer;
	GameEngineSoundPlayer BellPlayer;

	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;
	
	float OverlapTime = 0.0f;
	float SeagullTime = 0.0f;
	float WaveTime = 1;
	float BellTime = 1;

	int Set = 1;
	int AnimationSet = 1;

	int SeagullCount = 1;
	int WaveCount = 1;
	int BellCount = 1;
	
};

