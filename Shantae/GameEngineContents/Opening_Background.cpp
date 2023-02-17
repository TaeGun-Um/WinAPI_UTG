#include "Opening_Background.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Opening_Background::Opening_Background() 
{
}

Opening_Background::~Opening_Background() 
{
}

void Opening_Background::Start()
{
	GameEngineRender* Render = CreateRender("Opening_Background.Bmp", RenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());
}