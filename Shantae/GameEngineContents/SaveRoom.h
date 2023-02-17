#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;

// Ό³Έν :
class SaveRoom : public PlayLevel
{
public:
	// constrcuter destructer
	SaveRoom();
	~SaveRoom();

	// delete Function
	SaveRoom(const SaveRoom& _Other) = delete;
	SaveRoom(SaveRoom&& _Other) noexcept = delete;
	SaveRoom& operator=(const SaveRoom& _Other) = delete;
	SaveRoom& operator=(SaveRoom&& _Other) noexcept = delete;

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

