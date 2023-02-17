#include "SkyRoom_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

SkyRoom_Map::SkyRoom_Map() 
{
}

SkyRoom_Map::~SkyRoom_Map() 
{
}

void SkyRoom_Map::Start()
{
	GameEngineRender* Render = CreateRender("SkyRoom_Map.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}