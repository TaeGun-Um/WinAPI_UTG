#include "Scuttle_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* Scuttle_ColMap::ColMap = nullptr;

Scuttle_ColMap::Scuttle_ColMap() 
{
}

Scuttle_ColMap::~Scuttle_ColMap() 
{
}

void Scuttle_ColMap::Start()
{
	ColMap = CreateRender("Scuttle_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}