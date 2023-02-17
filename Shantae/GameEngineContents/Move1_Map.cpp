#include "Move1_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Move1_Map::Move1_Map() 
{
}

Move1_Map::~Move1_Map() 
{
}

void Move1_Map::Start()
{
	// 3788 217
	GameEngineRender* Render = CreateRender("Move1_Map.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}