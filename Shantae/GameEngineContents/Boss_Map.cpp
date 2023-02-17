#include "Boss_Map.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Boss_Map::Boss_Map() 
{
}

Boss_Map::~Boss_Map() 
{
}

void Boss_Map::Start()
{
	// 60 184
	GameEngineRender* Render = CreateRender("Boss_Map.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}