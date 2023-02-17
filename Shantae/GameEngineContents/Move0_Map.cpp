#include "Move0_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Move0_Map::Move0_Map() 
{
}

Move0_Map::~Move0_Map() 
{
}

void Move0_Map::Start()
{
	// 3876 142 27.3
	GameEngineRender* Render = CreateRender("Move0_Map.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}