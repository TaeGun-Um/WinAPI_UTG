#include "UncleRoom_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* UncleRoom_ColMap::ColMap = nullptr;

UncleRoom_ColMap::UncleRoom_ColMap() 
{
}

UncleRoom_ColMap::~UncleRoom_ColMap() 
{
}

void UncleRoom_ColMap::Start()
{
	ColMap = CreateRender("UncleRoom_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}