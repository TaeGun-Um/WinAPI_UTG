#include "Building0.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Building0::Building0()
{
}

Building0::~Building0()
{
}

void Building0::Start()
{
	GameEngineRender* Render = CreateRender("Building0.Bmp", RenderOrder::BackGround);
	// 40 56 0.714
	Render->SetPosition({ 1080, 480 });
	Render->SetScale({ 120, 168 });
}