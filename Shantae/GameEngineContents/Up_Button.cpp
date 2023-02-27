#include "Up_Button.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Up_Button::Up_Button() 
{
}

Up_Button::~Up_Button() 
{
}

void Up_Button::Start()
{
	AnimationRender = CreateRender("Up.Bmp", RenderOrder::Effect);
	AnimationRender->SetScale({ 60, 60 });
}
void Up_Button::Update(float _DeltaTime)
{

}
void Up_Button::Render(float _DeltaTime)
{

}