#include "SaveRoom_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

SaveRoom_Map::SaveRoom_Map() 
{
}

SaveRoom_Map::~SaveRoom_Map() 
{
}

void SaveRoom_Map::Start()
{
	GameEngineRender* Render = CreateRender("SaveRoom_Map.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}