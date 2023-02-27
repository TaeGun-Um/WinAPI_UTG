#include "Girl.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Girl::Girl() 
{
}

Girl::~Girl() 
{
}

void Girl::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Girl_L.bmp", .Start = 0, .End = 7, .InterTime = 0.15f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_L",  .ImageName = "Girl_L.bmp", .Start = 8, .End = 15, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Girl_R.bmp", .Start = 0, .End = 7, .InterTime = 0.15f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Girl_R.bmp", .Start = 8, .End = 15, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Run",  .ImageName = "Girl_L.bmp", .Start = 16, .End = 23, .InterTime = 0.1f });

	ChangeState(GirlState::IDLE);
}
void Girl::Update(float _DeltaTime)
{
	if (1 == CurrentPosCount)
	{
		CurrentPosCount = 0;
		CurrentPos = GetPos();
		LeftMovePos = CurrentPos + (float4::Left * 300);
	}

	UpdateState(_DeltaTime);
	DirectCheckForKill();
}
void Girl::Render(float _DeltaTime)
{

}

void Girl::DirectCheckForKill()
{
	float4 Pos = CurrentPos + (float4::Left * 1800);

	if (GetPos().x <= Pos.x)
	{
		Kill();
	}
}

void Girl::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}

std::string Girl::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;
	AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);

	if (true == MoveDirect)
	{
		DirString = "_L";
	}
	else if (false == MoveDirect)
	{
		DirString = "_R";
	}

	if (PrevDirString != DirString)
	{
		AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);
	}

	return DirString;
}