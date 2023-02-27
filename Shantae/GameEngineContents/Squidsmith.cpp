#include "Squidsmith.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
#include "Player.h"

Squidsmith::Squidsmith() 
{
}

Squidsmith::~Squidsmith() 
{
}

void Squidsmith::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Squidsmith_L.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_L",  .ImageName = "Squidsmith_L.bmp", .Start = 8, .End = 16, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Squidsmith_R.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_R",  .ImageName = "Squidsmith_R.bmp", .Start = 8, .End = 16, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 120, 100 });
	BodyCollision->SetPosition({ 0, -50 });
}
void Squidsmith::Update(float _DeltaTime)
{

}
void Squidsmith::Render(float _DeltaTime)
{

}

std::string Squidsmith::DirCheck(const std::string_view& _AnimationName)
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

void Squidsmith::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			int a = 0;
		}
	}
}

void Squidsmith::CharacterDirect()
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