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
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Desert_Man::Update(float _DeltaTime)
{
	if (1 == CurrentPosCount)
	{
		CurrentPosCount = 0;
		CurrentPos = GetPos();
	}

}
void Desert_Man::Render(float _DeltaTime)
{

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

void Desert_Man::DirectCheckForKill()
{
	float4 Pos = CurrentPos + (float4::Down * 1500);

	if (GetPos().y >= Pos.y)
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