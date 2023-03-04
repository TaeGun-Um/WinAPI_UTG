#include "Wavesplash.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
#include "Player.h"

Wavesplash::Wavesplash() 
{
}

Wavesplash::~Wavesplash() 
{
}

void Wavesplash::Start()
{
	GameEngineRender* Render3 = CreateRender("AnimationBox_Door.Bmp", RenderOrder::Object);
	Render3->SetPosition(Render3->GetImage()->GetImageScale().half());
	Render3->SetScale(Render3->GetImage()->GetImageScale());
	Render3->Off();

	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 150, 225 });
	BodyCollision->SetPosition({ 75, 112.5f });
}

void Wavesplash::Update(float _DeltaTime)
{
	//CreateSplash();
	
	//if (true == IsHelthWater)
	//{
	//	//HealthWater();
	//}
	
}