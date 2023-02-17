#include "HouseFront_PalmTree.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

HouseFront_PalmTree::HouseFront_PalmTree() 
{
}

HouseFront_PalmTree::~HouseFront_PalmTree() 
{
}

void HouseFront_PalmTree::Start()
{
	// 477 149 3.2
	GameEngineRender* Render = CreateRender("HouseFront_PalmTree.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 610, 380 });
	Render->SetScale({ 1536, 480 });
}