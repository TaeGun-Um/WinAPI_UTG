#include "BeforeBoss_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

BeforeBoss_Map::BeforeBoss_Map() 
{
}

BeforeBoss_Map::~BeforeBoss_Map() 
{
}

void BeforeBoss_Map::Start()
{
	GameEngineRender* Render = CreateRender("BeforeBoss_Map.Bmp", RenderOrder::BackGround);
	Render->SetPosition({650, 665});
	Render->SetScale(Render->GetImage()->GetImageScale());
}