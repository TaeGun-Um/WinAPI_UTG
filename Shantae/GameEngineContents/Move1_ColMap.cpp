#include "Move1_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* Move1_ColMap::ColMap = nullptr;

Move1_ColMap::Move1_ColMap() 
{
}

Move1_ColMap::~Move1_ColMap() 
{
}

void Move1_ColMap::Start()
{
	ColMap = CreateRender("Move1_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}