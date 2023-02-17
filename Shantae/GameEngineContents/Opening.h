#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

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

protected:
	void Loading();
	void Update(float _DeltaTime);

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:

};

