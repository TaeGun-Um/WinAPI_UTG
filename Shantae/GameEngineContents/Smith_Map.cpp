#include "Smith_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Smith_Map::Smith_Map() 
{
}

Smith_Map::~Smith_Map() 
{
}

void Smith_Map::Start()
{
	GameEngineRender* Render = CreateRender("Smith_Map.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}