#include "House_Interior.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

House_Interior::House_Interior()
{
}

House_Interior::~House_Interior()
{
}

void House_Interior::Start()
{
	GameEngineRender* Render = CreateRender("House_Interior.Bmp", RenderOrder::Object);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());
}