#include "TestMap.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

TestMap::TestMap() 
{
}

TestMap::~TestMap() 
{
}

void TestMap::Start()
{
	GameEngineRender* Render3 = CreateRender("TestMap.Bmp", RenderOrder::Map);
	Render3->SetPosition(Render3->GetImage()->GetImageScale().half());
	Render3->SetScale(Render3->GetImage()->GetImageScale());
}