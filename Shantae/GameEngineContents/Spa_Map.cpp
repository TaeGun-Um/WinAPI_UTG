#include "Spa_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Spa_Map::Spa_Map() 
{
}

Spa_Map::~Spa_Map() 
{
}

void Spa_Map::Start()
{
	GameEngineRender* Render = CreateRender("Spa_Map.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}