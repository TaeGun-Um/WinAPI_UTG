#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : 게임실행 버튼(250x100)
class SelectMenu_Button_Start : public GameEngineActor
{
public:
	static SelectMenu_Button_Start* StartB;

	// constrcuter destructer
	SelectMenu_Button_Start();
	~SelectMenu_Button_Start();

	// delete Function
	SelectMenu_Button_Start(const SelectMenu_Button_Start& _Other) = delete;
	SelectMenu_Button_Start(SelectMenu_Button_Start&& _Other) noexcept = delete;
	SelectMenu_Button_Start& operator=(const SelectMenu_Button_Start& _Other) = delete;
	SelectMenu_Button_Start& operator=(SelectMenu_Button_Start&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

