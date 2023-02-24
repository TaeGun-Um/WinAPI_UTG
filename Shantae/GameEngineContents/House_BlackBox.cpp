#include "House_BlackBox.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

House_BlackBox::House_BlackBox() 
{
}

House_BlackBox::~House_BlackBox() 
{
}

void House_BlackBox::Start()
{
	GameEngineRender* Render = CreateRender("BlackBox.Bmp", RenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}