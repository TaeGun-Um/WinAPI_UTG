#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;

// Ό³Έν : FieldLevel_3
class Move0 : public PlayLevel
{
public:
	static GameEngineSoundPlayer FieldBGMPlayer;

	// constrcuter destructer
	Move0();
	~Move0();

	// delete Function
	Move0(const Move0& _Other) = delete;
	Move0(Move0&& _Other) noexcept = delete;
	Move0& operator=(const Move0& _Other) = delete;
	Move0& operator=(Move0&& _Other) noexcept = delete;

protected:
	void Loading();
	void Update(float _DeltaTime);

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	void LevelSet();
	void Debugging();

	GameEngineSoundPlayer BGMPlayer;
	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;
	float OverlapTime = 0.0f;

	int Set = 1;
	int AnimationSet = 1;

};

