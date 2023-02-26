#include "TestRoomMap.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

TestRoomMap::TestRoomMap() 
{
}

TestRoomMap::~TestRoomMap() 
{
}

void TestRoomMap::Start()
{
	GameEngineRender* Render3 = CreateRender("TestRoomMap.Bmp", RenderOrder::Map);
	Render3->SetPosition(Render3->GetImage()->GetImageScale().half());
	Render3->SetScale(Render3->GetImage()->GetImageScale());
}