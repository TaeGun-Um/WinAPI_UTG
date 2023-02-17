#include "Smith_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* Smith_ColMap::ColMap = nullptr;

Smith_ColMap::Smith_ColMap() 
{
}

Smith_ColMap::~Smith_ColMap() 
{
}

void Smith_ColMap::Start()
{
	ColMap = CreateRender("Smith_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}