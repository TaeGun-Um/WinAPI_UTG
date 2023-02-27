#include "Stylist.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Stylist::Stylist() 
{
}

Stylist::~Stylist() 
{
}

void Stylist::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Stylist_L.bmp", .Start = 0, .End = 3, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_L",  .ImageName = "Stylist_R.bmp", .Start = 4, .End = 7, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_L",  .ImageName = "Stylist_L.bmp", .Start = 8, .End = 11, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Stylist_R.bmp", .Start = 0, .End = 3, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_R",  .ImageName = "Stylist_L.bmp", .Start = 4, .End = 7, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Stylist_R.bmp", .Start = 8, .End = 11, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Stylist_L.bmp", .Start = 12, .End = 15, .InterTime = 0.1f });

	ChangeState(StylistState::IDLE);
}
void Stylist::Update(float _DeltaTime)
{
	if (1 == CurrentPosCount)
	{
		CurrentPosCount = 0;
		CurrentPos = GetPos();
	}

	UpdateState(_DeltaTime);
	DirectCheckForKill();
}
void Stylist::Render(float _DeltaTime)
{

}

void Stylist::DirectCheckForKill()
{
	float4 Pos = CurrentPos + (float4::Left * 1800);

	if (GetPos().x <= Pos.x)
	{
		Kill();
	}
}

void Stylist::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}

std::string Stylist::DirCheck(const std::string_view& _AnimationName)
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