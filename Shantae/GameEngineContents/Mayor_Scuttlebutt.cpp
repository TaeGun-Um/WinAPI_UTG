#include "Mayor_Scuttlebutt.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

Mayor_Scuttlebutt::Mayor_Scuttlebutt() 
{
}

Mayor_Scuttlebutt::~Mayor_Scuttlebutt() 
{
}

void Mayor_Scuttlebutt::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Mayor Scuttlebutt_L.bmp", .Start = 0, .End = 3, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_L",  .ImageName = "Mayor Scuttlebutt_R.bmp", .Start = 4, .End = 7, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Mayor Scuttlebutt_R.bmp", .Start = 0, .End = 3, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_R",  .ImageName = "Mayor Scuttlebutt_L.bmp", .Start = 4, .End = 7, .InterTime = 0.1f });

}

void Mayor_Scuttlebutt::Update(float _DeltaTime)
{
	CharacterDirect();
	UpdateState(_DeltaTime);
}

void Mayor_Scuttlebutt::Render(float _DeltaTime)
{

}

void Mayor_Scuttlebutt::CharacterDirect()
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

std::string Mayor_Scuttlebutt::DirCheck(const std::string_view& _AnimationName)
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