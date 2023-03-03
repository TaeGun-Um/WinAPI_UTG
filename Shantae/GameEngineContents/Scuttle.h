#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class Inventory;
class BlackBox;
class BlueTextBox;
class Sea;

// Ό³Έν :
class Scuttle : public PlayLevel
{
public:
	static GameEngineSoundPlayer ScuttleBGMPlayer;
	static bool ScuttlePalyer;

	// constrcuter destructer
	Scuttle();
	~Scuttle();

	// delete Function
	Scuttle(const Scuttle& _Other) = delete;
	Scuttle(Scuttle&& _Other) noexcept = delete;
	Scuttle& operator=(const Scuttle& _Other) = delete;
	Scuttle& operator=(Scuttle&& _Other) noexcept = delete;

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
	void CameraAction();

	Sea* Se = nullptr;

	GameEngineSoundPlayer BGMPlayer;
	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;
	Inventory* Inven = nullptr;
	float OverlapTime = 0.0f;
	
	bool YCamera = false;
	bool IsStart = true;

	int StartCount = 0;
	int Set = 1;
	int AnimationSet = 1;
	int PortalSet = 1;
};

