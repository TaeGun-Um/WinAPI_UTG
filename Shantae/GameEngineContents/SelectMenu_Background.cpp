#include "SelectMenu_Background.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

SelectMenu_Background::SelectMenu_Background() 
{
}

SelectMenu_Background::~SelectMenu_Background() 
{
}

void SelectMenu_Background::Start()
{
	GameEngineRender* Render = CreateRender("SelectMenu_Background.Bmp", RenderOrder::Object);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());
}