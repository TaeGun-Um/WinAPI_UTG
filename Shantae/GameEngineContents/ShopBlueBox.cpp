#include "ShopBlueBox.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

ShopBlueBox::ShopBlueBox() 
{
}

ShopBlueBox::~ShopBlueBox() 
{
}

void ShopBlueBox::Start()
{
	// Animation
	AnimationRender = CreateRender("ShopBlueBox.Bmp", RenderOrder::UI);
	AnimationRender->SetScale({ 900, 900 });
	AnimationRender->SetPosition(GameEngineWindow::GetScreenSize().half() + float4::Down * 50);
	AnimationRender->SetAlpha(230);
	AnimationRender->EffectCameraOff();
}

void ShopBlueBox::Update(float _DeltaTime)
{
	
}

void ShopBlueBox::Render(float _DeltaTime)
{

}