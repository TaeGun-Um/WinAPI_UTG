#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;

// ���� :
class Shop : public PlayLevel
{
public:
	// constrcuter destructer
	Shop();
	~Shop();

	// delete Function
	Shop(const Shop& _Other) = delete;
	Shop(Shop&& _Other) noexcept = delete;
	Shop& operator=(const Shop& _Other) = delete;
	Shop& operator=(Shop&& _Other) noexcept = delete;

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
