#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;

// Ό³Έν : FieldLevel_5
class Stair : public PlayLevel
{
public:
	// constrcuter destructer
	Stair();
	~Stair();

	// delete Function
	Stair(const Stair& _Other) = delete;
	Stair(Stair&& _Other) noexcept = delete;
	Stair& operator=(const Stair& _Other) = delete;
	Stair& operator=(Stair&& _Other) noexcept = delete;

protected:
	void Loading();
	void Update(float _DeltaTime);

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	void LevelSet();
	void Debugging();
	void CameraAction();

	GameEngineSoundPlayer BGMPlayer;
	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;

	float OverlapTime = 0.0f; 
	bool YCamera = false;
	int Set = 1;
	int AnimationSet = 1;

};

