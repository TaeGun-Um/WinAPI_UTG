#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class Inventory;
class BlackBox;

// Ό³Έν : FieldLevel_3
class Move0 : public PlayLevel
{
public:
	static GameEngineSoundPlayer FieldBGMPlayer;

	// constrcuter destructer
	Move0();
	~Move0();

	// delete Function
	Move0(const Move0& _Other) = delete;
	Move0(Move0&& _Other) noexcept = delete;
	Move0& operator=(const Move0& _Other) = delete;
	Move0& operator=(Move0&& _Other) noexcept = delete;

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
	Inventory* Inven = nullptr;

	float OverlapTime = 0.0f;
	
	int Set = 1;
	int AnimationSet = 1;
	int RunAnimation = 1;

};

