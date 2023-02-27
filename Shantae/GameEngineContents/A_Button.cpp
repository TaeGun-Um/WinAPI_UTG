#include "A_Button.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

A_Button::A_Button() 
{
}

A_Button::~A_Button() 
{
}

void A_Button::Start()
{
	AnimationRender = CreateRender("A.Bmp", RenderOrder::Effect);
	AnimationRender->SetScale({ 400, 400 });
}
void A_Button::Update(float _DeltaTime)
{

}
void A_Button::Render(float _DeltaTime)
{

}