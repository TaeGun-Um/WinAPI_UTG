#include "Dancer.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Dancer::Dancer() 
{
}

Dancer::~Dancer() 
{
}

void Dancer::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Dancer_L.bmp", .Start = 0, .End = 7, .InterTime = 0.15f });
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Dancer_R.bmp", .Start = 0, .End = 7, .InterTime = 0.15f });
	
	AnimationRender->ChangeAnimation("Idle_L");
}
void Dancer::Update(float _DeltaTime)
{
	if (true == Direct && 1 == Set)
	{
		Set = 0;
		AnimationRender->ChangeAnimation("Idle_L");
	}
	else if (false == Direct && 1 == Set)
	{
		Set = 0;
		AnimationRender->ChangeAnimation("Idle_R");
	}
}
void Dancer::Render(float _DeltaTime)
{

}