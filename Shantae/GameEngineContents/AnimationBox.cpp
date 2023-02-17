#include "AnimationBox.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

AnimationBox::AnimationBox() 
{
}

AnimationBox::~AnimationBox() 
{
}

void AnimationBox::Start()
{
	GameEngineRender* Render3 = CreateRender("AnimationBox_Jump.Bmp", RenderOrder::BackGround);
	Render3->SetPosition({ 640, 286 });
	Render3->SetScale(Render3->GetImage()->GetImageScale());
	Render3->EffectCameraOff();

	GameEngineRender* Render1 = CreateRender("AnimationBox_Run.Bmp", RenderOrder::BackGround);
	Render1->SetPosition({ 640, 296 });
	Render1->SetScale(Render1->GetImage()->GetImageScale());
	Render1->EffectCameraOff();

	GameEngineRender* Render0 = CreateRender("AnimationBox_Idle.Bmp", RenderOrder::BackGround);
	Render0->SetPosition({ 640, 296 });
	Render0->SetScale(Render0->GetImage()->GetImageScale());
	Render0->EffectCameraOff();

	GameEngineRender* Render2 = CreateRender("AnimationBox_Spot.Bmp", RenderOrder::Map);
	Render2->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render2->SetScale(Render2->GetImage()->GetImageScale());
	Render2->EffectCameraOff();
}