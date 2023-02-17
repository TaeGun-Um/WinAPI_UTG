#include "House_Hut.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

House_Hut::House_Hut() 
{
}

House_Hut::~House_Hut() 
{
}

void House_Hut::Start()
{
	GameEngineRender* Render = CreateRender("House_Hut.Bmp", RenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());
}