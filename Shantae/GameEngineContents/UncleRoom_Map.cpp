#include "UncleRoom_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

UncleRoom_Map::UncleRoom_Map() 
{
}

UncleRoom_Map::~UncleRoom_Map() 
{
}

void UncleRoom_Map::Start()
{
	GameEngineRender* Render = CreateRender("UncleRoom_Map.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}