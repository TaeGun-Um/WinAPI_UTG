#include "SelectMenu_Button_Start.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

SelectMenu_Button_Start* SelectMenu_Button_Start::StartB = nullptr;

SelectMenu_Button_Start::SelectMenu_Button_Start() 
{
}

SelectMenu_Button_Start::~SelectMenu_Button_Start() 
{
}

void SelectMenu_Button_Start::Start()
{
	StartB = this;

	SetPos({ 340, 600 });

	GameEngineRender* Render = CreateRender("SelectMenu_Button_Start.Bmp", RenderOrder::Object);
	Render->SetScale({ 250, 100 });
}