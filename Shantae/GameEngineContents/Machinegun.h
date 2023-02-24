#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class BlackBox;

// Ό³Έν : FieldLevel_6
class Machinegun : public PlayLevel
{
public:
	// constrcuter destructer
	Machinegun();
	~Machinegun();

	// delete Function
	Machinegun(const Machinegun& _Other) = delete;
	Machinegun(Machinegun&& _Other) noexcept = delete;
	Machinegun& operator=(const Machinegun& _Other) = delete;
	Machinegun& operator=(Machinegun&& _Other) noexcept = delete;

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
	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;
	float OverlapTime = 0.0f;

	int Set = 1;
	int AnimationSet = 1;

};

