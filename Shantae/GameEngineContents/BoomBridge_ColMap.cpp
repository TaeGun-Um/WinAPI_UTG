#include "BoomBridge_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* BoomBridge_ColMap::ColMap = nullptr;

BoomBridge_ColMap::BoomBridge_ColMap() 
{
}

BoomBridge_ColMap::~BoomBridge_ColMap() 
{
}

void BoomBridge_ColMap::Start()
{
	ColMap = CreateRender("BoomBridge_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}