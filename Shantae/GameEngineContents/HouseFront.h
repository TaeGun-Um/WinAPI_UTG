#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;

// Ό³Έν : FieldLevel_2
class HouseFront : public PlayLevel
{
public:
	// constrcuter destructer
	HouseFront();
	~HouseFront();

	// delete Function
	HouseFront(const HouseFront& _Other) = delete;
	HouseFront(HouseFront&& _Other) noexcept = delete;
	HouseFront& operator=(const HouseFront& _Other) = delete;
	HouseFront& operator=(HouseFront&& _Other) noexcept = delete;

protected:
	void Loading();
	void Update(float _DeltaTime);

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	GameEngineSoundPlayer BGMPlayer;
	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;
	float OverlapTime = 0.0f;
	
	int Set = 1;

};

