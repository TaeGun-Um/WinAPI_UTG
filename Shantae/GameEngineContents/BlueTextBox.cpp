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

	OpenTime += _DeltaTime;

	if (0.1f <= OpenTime)
	{
		if (1 == TextCount)
		{
			TextCount = 0;
			TextCreate();
		}

		if (true == IsOver)
		{
			IsClose = true;

			if (1 == ScriptKill)
			{
				ScriptKill = 0;
				Scr->Kill();
				Scr = nullptr;
			}
			
			if (true == IsClose)
			{
				Close(_DeltaTime);
			}
		}
		else
		{
			if (GameEngineInput::IsDown("Select") && false == IsNext)
			{
				IsNext = true;
			}

			if (true == IsNext)
			{
				Cycle(_DeltaTime);
			}
		}
	}
}

void BlueTextBox::Cycle(float _DeltaTime)
{
	if (1 == CycleClose)
	{
		CycleClose = 0;

		Scr->TextOff();
		AnimationRender->ChangeAnimation("Close");
	}

	if (0 == CycleClose)
	{
		CycleTime += _DeltaTime;
	}

	if (0.1f <= CycleTime)
	{
		CycleOpen = 1;
	}

	if (1 == CycleOpen)
	{
		CycleOpen = 0;

		AnimationRender->ChangeAnimation("Open");

		if (0.2f <= CycleTime)
		{
			Scr->TextOn();
			Scr->NextScript();
			CycleTime = 0.0f;

			CycleClose = 1;
			IsNext = false;
		}
	}
}

void BlueTextBox::Open()
{
	AnimationRender->ChangeAnimation("Open");

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Inventory_in.wav");
	BGMPlayer.Volume(0.15f);
	BGMPlayer.LoopCount(1);
}

void BlueTextBox::Close(float _DeltaTime)
{
	CloseTime += _DeltaTime;

	AnimationRender->ChangeAnimation("Close");

	if (0.1f <= CloseTime)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Inventory_out.wav");
		BGMPlayer.Volume(0.15f);
		BGMPlayer.LoopCount(1);

		IsClose = false;
		Player::MainPlayer->BodyCollisionOn();
		Player::MainPlayer->ConversationOff();

		OpenTime = 0.0f;
		CloseTime = 0.0f;
		IsClose = false;
		Kill();
	}
}

void BlueTextBox::Kill()
{
	GameEngineActor* Act = AnimationRender->GetActor();
	Act->Death();
}

void BlueTextBox::TextCreate()
{
	float4 NewTPos = float4::Zero;
	Scr = GetLevel()->CreateActor<NPCScript>();
	Scr->SetPos(AnimationRender->GetPosition() + float4::Left * 325 + float4::Up * 65);
	Scr->SetNPCDialogType(static_cast<NPCDialogType_Dialog>(NPCValue));
}