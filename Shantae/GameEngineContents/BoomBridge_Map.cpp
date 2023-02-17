#include "BoomBridge_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

BoomBridge_Map::BoomBridge_Map() 
{
}

BoomBridge_Map::~BoomBridge_Map() 
{
}

void BoomBridge_Map::Start()
{
	GameEngineRender* Render = CreateRender("BoomBridge_Map.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}