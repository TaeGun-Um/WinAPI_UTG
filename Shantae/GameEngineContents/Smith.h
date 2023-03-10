#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class Inventory;
class BlackBox;
class BlueTextBox;
class Squidsmith;

// ???? :
class Smith : public PlayLevel
{
public:
	// constrcuter destructer
	Smith();
	~Smith();

	// delete Function
	Smith(const Smith& _Other) = delete;
	Smith(Smith&& _Other) noexcept = delete;
	Smith& operator=(const Smith& _Other) = delete;
	Smith& operator=(Smith&& _Other) noexcept = delete;
	
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
	Squidsmith* SmithNPC = nullptr;
	float OverlapTime = 0.0f;

	bool IsStart = true;

	int StartCount = 0;
	int Set = 1;
	int AnimationSet = 1;
	int HeartAction = 1;

};

