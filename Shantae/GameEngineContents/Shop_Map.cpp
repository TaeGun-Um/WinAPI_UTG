#include "Shop_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Shop_Map::Shop_Map() 
{
}

Shop_Map::~Shop_Map() 
{
}

void Shop_Map::Start()
{
	GameEngineRender* Render = CreateRender("Shop_Map.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}