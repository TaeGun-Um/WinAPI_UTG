#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class BlackBox;

// Ό³Έν : FieldLevel_9
class BeforeBoss : public PlayLevel
{
public:
	// constrcuter destructer
	BeforeBoss();
	~BeforeBoss();

	// delete Function
	BeforeBoss(const BeforeBoss& _Other) = delete;
	BeforeBoss(BeforeBoss&& _Other) noexcept = delete;
	BeforeBoss& operator=(const BeforeBoss& _Other) = delete;
	BeforeBoss& operator=(BeforeBoss&& _Other) noexcept = delete;

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

	GameEngineSoundPlayer BGMPlayer;
	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;
	float OverlapTime = 0.0f;

	int Set = 1;
	int AnimationSet = 1;

	bool IsBossDeath = false;

};

