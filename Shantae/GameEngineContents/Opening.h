#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"
#include "WhiteBox.h"
#include "BlackBox.h"

class WhiteBox;
class BlackBox;

// 설명 : 오프닝 화면
class Opening : public PlayLevel
{
public:
	// constrcuter destructer
	Opening();
	~Opening();

	// delete Function
	Opening(const Opening& _Other) = delete;
	Opening(Opening&& _Other) noexcept = delete;
	Opening& operator=(const Opening& _Other) = delete;
	Opening& operator=(Opening&& _Other) noexcept = delete;

	GameEngineSoundPlayer BGMPlayer;
	GameEngineSoundPlayer SelectPlayer;
	GameEngineSoundPlayer AnnouncePlayer;

protected:
	void Loading();
	void Update(float _DeltaTime);

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	void BlackBoxAnimation(float _DeltaTime);

	BlackBox* BBox = nullptr;
	WhiteBox* WBox = nullptr;
	int WBoxCount = 1;
	int BBoxCount = 1;

	float Delay = 0.0f;

};

