#include "SaveRoom_Front.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

SaveRoom_Front::SaveRoom_Front() 
{
}

SaveRoom_Front::~SaveRoom_Front() 
{
}

void SaveRoom_Front::Start()
{
	GameEngineRender* Render0 = CreateRender("SaveRoom_Front.Bmp", RenderOrder::Map);
	Render0->SetPosition(Render0->GetImage()->GetImageScale().half());
	Render0->SetScale(Render0->GetImage()->GetImageScale());

	GameEngineRender* Render1 = CreateRender("SaveRoom_Front2.Bmp", RenderOrder::Map);
	Render1->SetPosition(Render1->GetImage()->GetImageScale().half());
	Render1->SetScale(Render1->GetImage()->GetImageScale());
}