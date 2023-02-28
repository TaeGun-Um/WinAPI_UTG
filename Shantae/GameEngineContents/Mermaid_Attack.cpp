#include "Mermaid_Attack.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

Mermaid_Attack::Mermaid_Attack() 
{
}

Mermaid_Attack::~Mermaid_Attack() 
{
}

void Mermaid_Attack::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "ALL",  .ImageName = "Mermaid_R.bmp", .Start = 0, .End = 101, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::Monster);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 130, 150 });
	BodyCollision->SetPosition({ 30, -75 });
}
void Mermaid_Attack::Update(float _DeltaTime)
{

}
void Mermaid_Attack::Render(float _DeltaTime)
{

}

void Mermaid_Attack::DirectCheckForKill()
{
	float4 Pos = CurrentPos + (float4::Left * 2500);

	if (GetPos().x <= Pos.x)
	{
		Kill();
	}
}

void Mermaid_Attack::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}