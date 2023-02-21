#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;

// ���� :
class Scuttle : public PlayLevel
{
public:
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
	void LevelSet();
	void Debugging();
	void CameraAction();
	void Portal();

	GameEngineSoundPlayer BGMPlayer;
	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;
	Player* SHA = nullptr;
	float OverlapTime = 0.0f;
	
	bool YCamera = false;
	int Set = 1;
	int AnimationSet = 1;
};

