#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class Inventory;
class BlackBox;
class WhiteBox;
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
	void BlackBoxOutAnimation();
	void BlackBoxInAnimation();
	void InBoxKill();
	void WhiteBoxOutAnimation();
	void WhiteBoxInAnimation(float _DeltaTime);
	void InWBoxKill();

	BlackBox* BBoxOut = nullptr;
	BlackBox* BBoxIn = nullptr;
	int BBoxOutCount = 1;
	int BBoxInCount = 1;

	WhiteBox* WBoxOut = nullptr;
	WhiteBox* WBoxIn = nullptr;
	int WBoxOutCount = 1;
	int WBoxInCount = 1;
	int WBoxDelete = 1;

	void LevelSet();
	void Debugging();
	void CameraAction();

	GameEngineSoundPlayer BGMPlayer;
	GameEngineImage* ColMap = nullptr;
	GameEngineActor* Shantae = nullptr;
	GameEngineActor* Tank = nullptr;
	Player* SHA = nullptr;
	Inventory* Inven = nullptr;
	Boss_Tank* BOS = nullptr;
	
	float OverlapTime = 0.0f;
	float WhiteBoxTime = 0.0f;
	int Set = 1;
	int AnimationSet = 1;

	bool IsBossDeath = false;

};

