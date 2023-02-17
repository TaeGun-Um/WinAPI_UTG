#include "SelectMenu_Button_Test.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

SelectMenu_Button_Test* SelectMenu_Button_Test::TestB = nullptr;

SelectMenu_Button_Test::SelectMenu_Button_Test()
{
}

SelectMenu_Button_Test::~SelectMenu_Button_Test()
{
}

void SelectMenu_Button_Test::Start()
{
	TestB = this;

	SetPos({ 640, 600 });

	GameEngineRender* Render = CreateRender("SelectMenu_Button_Test.Bmp", RenderOrder::Object);
	Render->SetScale({ 250, 100 });
}
