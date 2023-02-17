#include "Machinegun_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* Machinegun_ColMap::ColMap = nullptr;

Machinegun_ColMap::Machinegun_ColMap() 
{
}

Machinegun_ColMap::~Machinegun_ColMap() 
{
}

void Machinegun_ColMap::Start()
{
	ColMap = CreateRender("Machinegun_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}