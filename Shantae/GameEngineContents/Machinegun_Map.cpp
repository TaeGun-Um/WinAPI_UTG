#include "Machinegun_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Machinegun_Map::Machinegun_Map() 
{
}

Machinegun_Map::~Machinegun_Map() 
{
}

void Machinegun_Map::Start()
{
	GameEngineRender* Render = CreateRender("Machinegun_Map.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}