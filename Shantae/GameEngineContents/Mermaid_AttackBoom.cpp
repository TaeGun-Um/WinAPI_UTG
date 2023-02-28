#include "Mermaid_AttackBoom.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

Mermaid_AttackBoom::Mermaid_AttackBoom() 
{
}

Mermaid_AttackBoom::~Mermaid_AttackBoom() 
{
}

void Mermaid_AttackBoom::Start()
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
void Mermaid_AttackBoom::Update(float _DeltaTime)
{

}
void Mermaid_AttackBoom::Render(float _DeltaTime)
{

}

void Mermaid_AttackBoom::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}