#include "Desert_Man.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Desert_Man::Desert_Man() 
{
}

Desert_Man::~Desert_Man() 
{
}

void Desert_Man::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Desert Man_L.bmp", .Start = 0, .End = 5, .InterTime = 0.15f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_L",  .ImageName = "Desert Man_R.bmp", .Start = 6, .End = 10, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_L",  .ImageName = "Desert Man_L.bmp", .Start = 11, .End = 18, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Desert Man_R.bmp", .Start = 0, .End = 5, .InterTime = 0.15f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_R",  .ImageName = "Desert Man_L.bmp", .Start = 6, .End = 10, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Desert Man_R.bmp", .Start = 11, .End = 18, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Run",  .ImageName = "Desert Man_L.bmp", .Start = 19, .End = 26, .InterTime = 0.1f });

	ChangeState(Desert_ManState::IDLE);
}
void Desert_Man::Update(float _DeltaTime)
{
	if (1 == CurrentPosCount)
	{
		CurrentPosCount = 0;
		CurrentPos = GetPos();
		LeftMovePos = CurrentPos + (float4::Left * 350);
	}

	UpdateState(_DeltaTime);
	DirectCheckForKill();
}
void Desert_Man::Render(float _DeltaTime)
{

}

void Desert_Man::DirectCheckForKill()
{
	float4 Pos = CurrentPos + (float4::Left * 1800);

	if (GetPos().x <= Pos.x)
	{
		Kill();
	}
}

void Desert_Man::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}

std::string Desert_Man::DirCheck(const std::string_view& _AnimationName)
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