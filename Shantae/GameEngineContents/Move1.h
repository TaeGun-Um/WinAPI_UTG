#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class BlackBox;

// Ό³Έν : FieldLevel_4
class Move1 : public PlayLevel
{
public:
	// constrcuter destructer
	Move1();
	~Move1();

	// delete Function
	Move1(const Move1& _Other) = delete;
	Move1(Move1&& _Other) noexcept = delete;
	Move1& operator=(const Move1& _Other) = delete;
	Move1& operator=(Move1&& _Other) noexcept = delete;

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
	void CameraAction();

	GameEngineSoundPlayer BGMPlayer;
	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;

	float OverlapTime = 0.0f;
	int Set = 1;
	int AnimationSet = 1;

};

