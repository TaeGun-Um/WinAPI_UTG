#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"
#include "WhiteBox.h"
#include "BlackBox.h"

class WhiteBox;
class BlackBox;

// 설명 : 오프닝 화면
class EndingLevel : public PlayLevel
{
public:
	// constrcuter destructer
	EndingLevel();
	~EndingLevel();

	// delete Function
	EndingLevel(const EndingLevel& _Other) = delete;
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

protected:
	void Loading();
	void Update(float _DeltaTime);

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	void Debugging();
	void BlackBoxAnimation(float _DeltaTime);
	GameEngineSoundPlayer BGMPlayer;

	BlackBox* BBox = nullptr;
	WhiteBox* WBox = nullptr;
	int WBoxCount = 1;
	int BBoxCount = 1;

	float Delay = 0.0f;

};

