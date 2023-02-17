#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

// 설명 : 메뉴 화면
class SelectMeun : public PlayLevel
{
public:
	// constrcuter destructer
	SelectMeun();
	~SelectMeun();

	// delete Function
	SelectMeun(const SelectMeun& _Other) = delete;
	SelectMeun(SelectMeun&& _Other) noexcept = delete;
	SelectMeun& operator=(const SelectMeun& _Other) = delete;
	SelectMeun& operator=(SelectMeun&& _Other) noexcept = delete;

	GameEngineSoundPlayer BGMPlayer;

protected:
	void Loading();
	void Update(float _DeltaTime);

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	// 0201
	float Time = 0.0f;
	float4 Start = float4::Zero;
	float4 End = float4::Zero;
};

