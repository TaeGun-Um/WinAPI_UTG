#include "Icon.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Icon::Icon() 
{
}

Icon::~Icon() 
{
}

void Icon::Start()
{
	AnimationRender = CreateRender(RenderOrder::UI);
	AnimationRender->SetScale({ 300, 300 });
	AnimationRender->CreateAnimation({ .AnimationName = "MonsterMilk",  .ImageName = "Items.bmp", .Start = 1, .End = 1, .InterTime = 10.0f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Meat",  .ImageName = "Items.bmp", .Start = 2, .End = 2, .InterTime = 10.0f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Bubble",  .ImageName = "Items.bmp", .Start = 5, .End = 5, .InterTime = 10.0f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "PikeBall",  .ImageName = "Items.bmp", .Start = 6, .End = 6, .InterTime = 10.0f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Octopus",  .ImageName = "Items.bmp", .Start = 8, .End = 8, .InterTime = 10.0f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Pass",  .ImageName = "Items.bmp", .Start = 10, .End = 10, .InterTime = 10.0f, .Loop = false });
	
	AnimationRender->ChangeAnimation("Meat");
}

void Icon::Update(float _DeltaTime)
{
	if (1 == Count)
	{
		AnimationRender->ChangeAnimation("MonsterMilk");
	}
	else if (2 == Count)
	{
		AnimationRender->ChangeAnimation("Bubble");
	}
	else if (3 == Count)
	{
		AnimationRender->ChangeAnimation("Octopus");
	}
}

void Icon::Render(float _DeltaTime)
{

}