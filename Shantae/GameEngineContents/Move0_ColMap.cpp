#include "Move0_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* Move0_ColMap::ColMap = nullptr;

Move0_ColMap::Move0_ColMap() 
{
}

Move0_ColMap::~Move0_ColMap() 
{
}

void Move0_ColMap::Start()
{
	ColMap = CreateRender("Move0_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}