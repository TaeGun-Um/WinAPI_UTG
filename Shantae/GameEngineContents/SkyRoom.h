#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class Inventory;
class BlackBox;
class BlueTextBox;

// ???? :
class SkyRoom : public PlayLevel
{
public:
	// constrcuter destructer
	SkyRoom();
	~SkyRoom();

	// delete Function
	SkyRoom(const SkyRoom& _Other) = delete;
	SkyRoom(SkyRoom&& _Other) noexcept = delete;
	SkyRoom& operator=(const SkyRoom& _Other) = delete;
	SkyRoom& operator=(SkyRoom&& _Other) noexcept = delete;

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
	BlueTextBox* BTB = nullptr;
	int BBoxOutCount = 1;
	int BBoxInCount = 1;

	void LevelSet();
	void Debugging();

	GameEngineSoundPlayer BGMPlayer;
	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;
	Inventory* Inven = nullptr;
	float OverlapTime = 0.0f;

	bool IsStart = true;

	int StartCount = 0;
	int Set = 1;
	int AnimationSet = 1;

};

