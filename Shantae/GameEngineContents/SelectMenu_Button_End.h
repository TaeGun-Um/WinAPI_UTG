#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : 게임종료 버튼(250x100)
class SelectMenu_Button_End : public GameEngineActor
{
public:
	static SelectMenu_Button_End* EndB;

	// constrcuter destructer
	SelectMenu_Button_End();
	~SelectMenu_Button_End();

	// delete Function
	SelectMenu_Button_End(const SelectMenu_Button_End& _Other) = delete;
	SelectMenu_Button_End(SelectMenu_Button_End&& _Other) noexcept = delete;
	SelectMenu_Button_End& operator=(const SelectMenu_Button_End& _Other) = delete;
	SelectMenu_Button_End& operator=(SelectMenu_Button_End&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

