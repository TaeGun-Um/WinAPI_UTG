#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : 테스트 버튼(250x100)
class SelectMenu_Button_Test : public GameEngineActor
{
public:
	static SelectMenu_Button_Test* TestB;

	// constrcuter destructer
	SelectMenu_Button_Test();
	~SelectMenu_Button_Test();

	// delete Function
	SelectMenu_Button_Test(const SelectMenu_Button_Test& _Other) = delete;
	SelectMenu_Button_Test(SelectMenu_Button_Test&& _Other) noexcept = delete;
	SelectMenu_Button_Test& operator=(const SelectMenu_Button_Test& _Other) = delete;
	SelectMenu_Button_Test& operator=(SelectMenu_Button_Test&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

