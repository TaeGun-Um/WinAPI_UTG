#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;

// Ό³Έν :
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
	GameEngineSoundPlayer BGMPlayer;
	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;
	float OverlapTime = 0.0f;

	int Set = 1;

};

