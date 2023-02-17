#include "UncleRoom_Front.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

UncleRoom_Front::UncleRoom_Front() 
{
}

UncleRoom_Front::~UncleRoom_Front() 
{
}

void UncleRoom_Front::Start()
{
	GameEngineRender* Render = CreateRender("UncleRoom_Front.Bmp", RenderOrder::Map);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}