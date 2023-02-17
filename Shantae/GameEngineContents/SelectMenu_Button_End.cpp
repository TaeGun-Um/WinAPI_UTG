#include "SelectMenu_Button_End.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

SelectMenu_Button_End* SelectMenu_Button_End::EndB = nullptr;

SelectMenu_Button_End::SelectMenu_Button_End() 
{
}

SelectMenu_Button_End::~SelectMenu_Button_End() 
{
}

void SelectMenu_Button_End::Start()
{
	EndB = this;

	SetPos({ 940, 600 });

	GameEngineRender* Render = CreateRender("SelectMenu_Button_End.Bmp", RenderOrder::Object);
	Render->SetScale({ 250, 100 });
}