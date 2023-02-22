#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// 설명 : 버튼 선택 아이콘
class SelectMenu_Icon : public GameEngineActor
{
public:
	// constrcuter destructer
	SelectMenu_Icon();
	~SelectMenu_Icon();

	// delete Function
	SelectMenu_Icon(const SelectMenu_Icon& _Other) = delete;
	SelectMenu_Icon(SelectMenu_Icon&& _Other) noexcept = delete;
	SelectMenu_Icon& operator=(const SelectMenu_Icon& _Other) = delete;
	SelectMenu_Icon& operator=(SelectMenu_Icon&& _Other) noexcept = delete;

	GameEngineSoundPlayer BGMPlayer;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float OverlapTime = 0.0f;
	float DelayTime = 0.2f;
	float SelectTime = 0.0f;

	bool GameStart = false;
	bool GameTest = false;
	bool GameEnd = false;
	bool SelectTimeon = false;
};

