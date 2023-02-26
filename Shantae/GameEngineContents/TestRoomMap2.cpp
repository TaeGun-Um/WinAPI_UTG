#include "TestRoomMap2.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

TestRoomMap2::TestRoomMap2() 
{
}

TestRoomMap2::~TestRoomMap2() 
{
}

void TestRoomMap2::Start()
{
	GameEngineRender* Render3 = CreateRender("TestRoomMap2.Bmp", RenderOrder::Map);
	Render3->SetPosition(Render3->GetImage()->GetImageScale().half());
	Render3->SetScale(Render3->GetImage()->GetImageScale());
}