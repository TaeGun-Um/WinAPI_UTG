#include "Stair_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Stair_Map::Stair_Map() 
{
}

Stair_Map::~Stair_Map() 
{
}

void Stair_Map::Start()
{
	// 538 1182
	GameEngineRender* Render = CreateRender("Stair_Map.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}