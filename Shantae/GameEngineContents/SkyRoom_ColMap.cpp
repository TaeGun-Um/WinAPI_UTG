#include "SkyRoom_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* SkyRoom_ColMap::ColMap = nullptr;

SkyRoom_ColMap::SkyRoom_ColMap() 
{
}

SkyRoom_ColMap::~SkyRoom_ColMap() 
{
}

void SkyRoom_ColMap::Start()
{
	ColMap = CreateRender("SkyRoom_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}