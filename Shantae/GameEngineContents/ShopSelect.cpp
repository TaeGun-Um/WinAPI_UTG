#include "ShopSelect.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

ShopSelect::ShopSelect() 
{
}

ShopSelect::~ShopSelect() 
{
}

void ShopSelect::Start()
{
	// Animation
	AnimationRender = CreateRender("ShopSelect.Bmp", RenderOrder::UI);
	AnimationRender->SetScale({ 100, 100 });

	AnimationRender->EffectCameraOff();
}

void ShopSelect::Update(float _DeltaTime)
{
	
}

void ShopSelect::Render(float _DeltaTime)
{

}