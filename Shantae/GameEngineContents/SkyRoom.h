#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class BlackBox;

// Ό³Έν :
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
	void BlackBoxAnimation(float _DeltaTime);
	void LevelSet();
	void Debugging();

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

