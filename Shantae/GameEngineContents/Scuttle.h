#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class BlackBox;

// Ό³Έν :
class Scuttle : public PlayLevel
{
public:
	static GameEngineSoundPlayer ScuttleBGMPlayer;

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
	void BlackBoxAnimation(float _DeltaTime);
	void LevelSet();
	void Debugging();
	void CameraAction();
	void Portal();

	BlackBox* BBoxOut = nullptr;
	BlackBox* BBoxIn = nullptr;
	int BBoxOutCount = 1;
	int BBoxInCount = 1;

	GameEngineSoundPlayer BGMPlayer;
	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;
	float OverlapTime = 0.0f;
	
	bool YCamera = false;
	bool ScuttlePalyer = false;

	int Set = 1;
	int AnimationSet = 1;
};

