#include "Boy.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Boy::Boy() 
{
}

Boy::~Boy() 
{
}

void Boy::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Boy_L.bmp", .Start = 0, .End = 4, .InterTime = 0.15f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_L",  .ImageName = "Boy_L.bmp", .Start = 5, .End = 12, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Boy_R.bmp", .Start = 0, .End = 4, .InterTime = 0.15f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Boy_R.bmp", .Start = 5, .End = 12, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Run",  .ImageName = "Boy_L.bmp", .Start = 13, .End = 20, .InterTime = 0.1f });

	ChangeState(BoyState::IDLE);
}
void Boy::Update(float _DeltaTime)
{
	if (1 == CurrentPosCount)
	{
		CurrentPosCount = 0;
		CurrentPos = GetPos();
		LeftMovePos = CurrentPos + (float4::Left * 500);
	}

	UpdateState(_DeltaTime);
	DirectCheckForKill();
}
void Boy::Render(float _DeltaTime)
{

}

void Boy::DirectCheckForKill()
{
	float4 Pos = CurrentPos + (float4::Left * 2500);

	if (GetPos().x <= Pos.x)
	{
		Kill();
	}
}

void Boy::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}

std::string Boy::DirCheck(const std::string_view& _AnimationName)
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