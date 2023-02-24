#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class BlackBox;

// Ό³Έν :
class UncleRoom : public PlayLevel
{
public:
	// constrcuter destructer
	UncleRoom();
	~UncleRoom();

	// delete Function
	UncleRoom(const UncleRoom& _Other) = delete;
	UncleRoom(UncleRoom&& _Other) noexcept = delete;
	UncleRoom& operator=(const UncleRoom& _Other) = delete;
	UncleRoom& operator=(UncleRoom&& _Other) noexcept = delete;

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

