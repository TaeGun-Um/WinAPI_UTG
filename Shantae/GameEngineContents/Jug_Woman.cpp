#include "Jug_Woman.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Jug_Woman::Jug_Woman() 
{
}

Jug_Woman::~Jug_Woman() 
{
}

void Jug_Woman::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Jug Woman_L.bmp", .Start = 0, .End = 7, .InterTime = 0.15f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_L",  .ImageName = "Jug Woman_R.bmp", .Start = 8, .End = 11, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_L",  .ImageName = "Jug Woman_L.bmp", .Start = 12, .End = 19, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Jug Woman_R.bmp", .Start = 0, .End = 7, .InterTime = 0.15f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_R",  .ImageName = "Jug Woman_L.bmp", .Start = 8, .End = 11, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Jug Woman_R.bmp", .Start = 12, .End = 19, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Run",  .ImageName = "Jug Woman_L.bmp", .Start = 20, .End = 27, .InterTime = 0.1f });

	ChangeState(Jug_WomanState::IDLE);
}
void Jug_Woman::Update(float _DeltaTime)
{
	if (1 == CurrentPosCount)
	{
		CurrentPosCount = 0;
		CurrentPos = GetPos();
		LeftMovePos = CurrentPos + (float4::Left * 385);
	}

	UpdateState(_DeltaTime);
	DirectCheckForKill();
}
void Jug_Woman::Render(float _DeltaTime)
{

}

void Jug_Woman::DirectCheckForKill()
{
	float4 Pos = CurrentPos + (float4::Left * 1800);

	if (GetPos().x <= Pos.x)
	{
		Kill();
	}
}

void Jug_Woman::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}

std::string Jug_Woman::DirCheck(const std::string_view& _AnimationName)
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