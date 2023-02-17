#include "Boss_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* Boss_ColMap::ColMap = nullptr;

Boss_ColMap::Boss_ColMap() 
{
}

Boss_ColMap::~Boss_ColMap() 
{
}

void Boss_ColMap::Start()
{
	ColMap = CreateRender("Boss_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}