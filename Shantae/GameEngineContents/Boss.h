#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class BlackBox;
class Boss_Tank;

// Ό³Έν : FieldLevel_10
class Boss : public PlayLevel
{
public:
	// constrcuter destructer
	Boss();
	~Boss();

	// delete Function
	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;

protected:
	void Loading();
	void Update(float _DeltaTime);

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	void BlackBoxAnimation(float _DeltaTime);
	void LevelSet();
	void Debugging();
	void CameraAction();

	BlackBox* BBoxOut = nullptr;
	BlackBox* BBoxIn = nullptr;
	int BBoxOutCount = 1;
	int BBoxInCount = 1;

	GameEngineSoundPlayer BGMPlayer;
	GameEngineImage* ColMap = nullptr;
	GameEngineActor* Shantae = nullptr;
	GameEngineActor* Tank = nullptr;
	Player* SHA = nullptr;
	Boss_Tank* BOS = nullptr;
	
	float OverlapTime = 0.0f;
	int Set = 1;
	int AnimationSet = 1;

};

