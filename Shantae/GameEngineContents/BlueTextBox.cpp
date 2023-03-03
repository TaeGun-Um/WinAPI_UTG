#include "BlueTextBox.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "NPCScript.h"
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

	AnimationRender = CreateRender(RenderOrder::UI);
	AnimationRender->SetScale({ 900, 900 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Open",  .ImageName = "BlueTextBox_Open.bmp", .Start = 0, .End = 2, .InterTime = 0.05f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Opening",  .ImageName = "BlueTextBox_Open.bmp", .Start = 2, .End = 2, .InterTime = 0.05f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Close",  .ImageName = "BlueTextBox_Close.bmp", .Start = 0, .End = 2, .InterTime = 0.05f, .Loop = false });

	AnimationRender->SetPosition(GameEngineWindow::GetScreenSize().half() + float4::Up * 100);
	AnimationRender->EffectCameraOff();
	AnimationRender->SetAlpha(230);

	// state
	IsOpen = true;
	AnimationRender->ChangeAnimation("Open");

}

void BlueTextBox::Update(float _DeltaTime)
{
	if (true == IsOpen)
	{
		IsOpen = false;
		Open();
	}

	if (false == IsOpen && 1 == TextCount)
	{
		TextCount = 0;
		TextCreate();
	}
	

	//if (GameEngineInput::IsDown("Fire") && false == IsOpen
	//	&& true == AnimationRender->IsUpdate())
	//{
	//	IsClose = true;
	//}

	//if (true == IsClose)
	//{
	//	Close();
	//}
}

void BlueTextBox::Render(float _DeltaTime)
{

}

void BlueTextBox::Open()
{
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
		IsClose = false;

		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Inventory_out.wav");
		BGMPlayer.Volume(0.15f);
		BGMPlayer.LoopCount(1);

		Player::MainPlayer->BodyCollisionOn();
	}
}

void BlueTextBox::TextCreate()
{
	NPCScript* Scr = nullptr;
	float4 NewTPos = float4::Zero;

	Scr = GetLevel()->CreateActor<NPCScript>();
	Scr->SetPos(AnimationRender->GetPosition() + float4::Left * 325 + float4::Up * 65);
}