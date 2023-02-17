#include "SaveRoom_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* SaveRoom_ColMap::ColMap = nullptr;

SaveRoom_ColMap::SaveRoom_ColMap() 
{
}

SaveRoom_ColMap::~SaveRoom_ColMap() 
{
}

void SaveRoom_ColMap::Start()
{
	ColMap = CreateRender("SaveRoom_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}