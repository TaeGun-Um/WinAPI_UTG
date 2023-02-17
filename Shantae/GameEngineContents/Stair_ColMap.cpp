#include "Stair_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* Stair_ColMap::ColMap = nullptr;

Stair_ColMap::Stair_ColMap() 
{
}

Stair_ColMap::~Stair_ColMap() 
{
}

void Stair_ColMap::Start()
{
	ColMap = CreateRender("Stair_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}