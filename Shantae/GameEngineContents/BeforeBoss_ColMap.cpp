#include "BeforeBoss_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* BeforeBoss_ColMap::ColMap = nullptr;

BeforeBoss_ColMap::BeforeBoss_ColMap() 
{
}

BeforeBoss_ColMap::~BeforeBoss_ColMap() 
{
}

void BeforeBoss_ColMap::Start()
{
	ColMap = CreateRender("BeforeBoss_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}