#include "Spa_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* Spa_ColMap::ColMap = nullptr;

Spa_ColMap::Spa_ColMap() 
{
}

Spa_ColMap::~Spa_ColMap() 
{
}

void Spa_ColMap::Start()
{
	ColMap = CreateRender("Spa_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}