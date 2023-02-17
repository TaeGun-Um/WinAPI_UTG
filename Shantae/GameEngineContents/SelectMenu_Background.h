#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : 게임 선택창 배경(1280x720)
class SelectMenu_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	SelectMenu_Background();
	~SelectMenu_Background();

	// delete Function
	SelectMenu_Background(const SelectMenu_Background& _Other) = delete;
	SelectMenu_Background(SelectMenu_Background&& _Other) noexcept = delete;
	SelectMenu_Background& operator=(const SelectMenu_Background& _Other) = delete;
	SelectMenu_Background& operator=(SelectMenu_Background&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

