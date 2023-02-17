#include "Shop_Front.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Shop_Front::Shop_Front() 
{
}

Shop_Front::~Shop_Front() 
{
}

void Shop_Front::Start()
{
	GameEngineRender* Render = CreateRender("Shop_Front.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}