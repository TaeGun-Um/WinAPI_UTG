#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;

// Ό³Έν :
class Spa : public PlayLevel
{
public:
	// constrcuter destructer
	Spa();
	~Spa();

	// delete Function
	Spa(const Spa& _Other) = delete;
	Spa(Spa&& _Other) noexcept = delete;
	Spa& operator=(const Spa& _Other) = delete;
	Spa& operator=(Spa&& _Other) noexcept = delete;

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
	int AnimationSet = 1;

};

