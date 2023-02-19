#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
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
	GameEngineSoundPlayer BGMPlayer;

	GameEngineActor* Shantae = nullptr;
	Player* SHA = nullptr;

	GameEngineActor* Tank = nullptr;
	Boss_Tank* BOS = nullptr;

	GameEngineImage* ColMap = nullptr;
	
	float OverlapTime = 0.0f;

};

