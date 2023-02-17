#include "Scuttle_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Scuttle_Map::Scuttle_Map() 
{
}

Scuttle_Map::~Scuttle_Map() 
{
}

void Scuttle_Map::Start()
{
	GameEngineRender* Render = CreateRender("Scuttle_Map.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}