#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;

// Ό³Έν : FieldLevel_1
class House : public PlayLevel
{
public:
	// constrcuter destructer
	House();
	~House();

	// delete Function
	House(const House& _Other) = delete;
	House(House&& _Other) noexcept = delete;
	House& operator=(const House& _Other) = delete;
	House& operator=(House&& _Other) noexcept = delete;

protected:
	void Loading();
	void Update(float _DeltaTime);

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	void LevelSet();
	void Debugging();
	void AnimationChange();
	void SoundCombination();

	float OverlapTime = 0.0f;
	int Change = 0;

};

