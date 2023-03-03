#include "BlueTextBox.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

BlueTextBox* BlueTextBox::DialogTextBox = nullptr;

BlueTextBox::BlueTextBox() 
{
}

BlueTextBox::~BlueTextBox() 
{
}



void BlueTextBox::Start()
{
	DialogTextBox = this;

	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Open",  .ImageName = "BlueTextBox_Open.bmp", .Start = 0, .End = 2, .InterTime = 0.05f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Opening",  .ImageName = "BlueTextBox_Open.bmp", .Start = 2, .End = 2, .InterTime = 0.05f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Close",  .ImageName = "BlueTextBox_Close.bmp", .Start = 0, .End = 2, .InterTime = 0.05f, .Loop = false });

	AnimationRender->SetPosition(GameEngineWindow::GetScreenSize().half());
	AnimationRender->EffectCameraOff();
	AnimationRender->Off();

	// state
	AnimationRender->ChangeAnimation("Open");

	// TextCreate();
}

void BlueTextBox::Update(float _DeltaTime)
{
	if (true == IsOpen)
	{
		IsOpen = false;
		Open();
	}

	if (GameEngineInput::IsDown("Fire") && false == IsOpen)
	{
		IsClose = true;
	}

	if (true == IsClose)
	{
		IsClose = false;
		Close();
	}
}

void BlueTextBox::Render(float _DeltaTime)
{

}

void BlueTextBox::Open()
{
	AnimationRender->On();

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Inventory_in.wav");
	BGMPlayer.Volume(0.15f);
	BGMPlayer.LoopCount(1);

	AnimationRender->ChangeAnimation("Open");
}

void BlueTextBox::Close()
{
	AnimationRender->ChangeAnimation("Close");

	if (true == AnimationRender->IsAnimationEnd())
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Inventory_out.wav");
		BGMPlayer.Volume(0.15f);
		BGMPlayer.LoopCount(1);

		AnimationRender->Off();
	}
}

// void BlueTextBox::TextCreate() {}