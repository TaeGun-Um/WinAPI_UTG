#include "Sailor.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

Sailor::Sailor() 
{
}

Sailor::~Sailor() 
{
}

void Sailor::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Sailor_L.bmp", .Start = 0, .End = 4, .InterTime = 0.15f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_L",  .ImageName = "Sailor_R.bmp", .Start = 5, .End = 10, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Sailor_R.bmp", .Start = 0, .End = 4, .InterTime = 0.15f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_R",  .ImageName = "Sailor_L.bmp", .Start = 5, .End = 10, .InterTime = 0.1f });

	ChangeState(SailorState::IDLE);
}
void Sailor::Update(float _DeltaTime)
{
	CharacterDirect();
	UpdateState(_DeltaTime);
}
void Sailor::Render(float _DeltaTime)
{

}

void Sailor::CharacterDirect()
{
	float interval = Player::MainPlayer->GetPos().x - GetPos().x;

	if (0.0f >= interval)
	{
		MoveDirect = true;
	}
	else
	{
		MoveDirect = false;
	}
}

std::string Sailor::DirCheck(const std::string_view& _AnimationName)
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
		Isturn = true;
	}

	return DirString;
}