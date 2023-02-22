#include "SelectMenu_Icon.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "SelectMenu_Button_Start.h"
#include "SelectMenu_Button_Test.h"
#include "SelectMenu_Button_End.h"
#include "ContentsEnum.h"

SelectMenu_Icon::SelectMenu_Icon() 
{
}

SelectMenu_Icon::~SelectMenu_Icon() 
{
}

void SelectMenu_Icon::Start()
{
	SetPos(SelectMenu_Button_Start::StartB->GetPos());

	GameEngineRender* Render = CreateRender("SelectMenu_Icon.Bmp", RenderOrder::Player);
	Render->SetScale({ 260, 110 });
}

void SelectMenu_Icon::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Select"))
	{
		if (GetPos().ix() == SelectMenu_Button_Start::StartB->GetPos().ix())
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_select.wav");
			BGMPlayer.Volume(0.1f);
			BGMPlayer.LoopCount(1);
			GameStart = true;
		}
		if (GetPos().ix() == SelectMenu_Button_Test::TestB->GetPos().ix())
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_select.wav");
			BGMPlayer.Volume(0.1f);
			BGMPlayer.LoopCount(1);
			GameTest = true;
		}
		if (GetPos().ix() == SelectMenu_Button_End::EndB->GetPos().ix())
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_select.wav");
			BGMPlayer.Volume(0.1f);
			BGMPlayer.LoopCount(1);
			GameEnd = true;
		}

		SelectTimeon = true;
	}

	if (true == SelectTimeon)
	{
		SelectTime += _DeltaTime;

		if (SelectTime >= 2.0f)
		{
			if (true == GameStart)
			{
				GameEngineCore::GetInst()->ChangeLevel("House");
				SelectTime = 0.0f;
				GameStart = false;
				SelectTimeon = false;
			}
			if (true == GameTest)
			{
				GameEngineCore::GetInst()->ChangeLevel("TestLevel");
				SelectTime = 0.0f;
				GameTest = false;
				SelectTimeon = false;
			}
			if (true == GameEnd)
			{
				GameEngineWindow::AppOff();
				SelectTime = 0.0f;
				GameEnd = false;
				SelectTimeon = false;
			}
		}
		return;
	}

	OverlapTime += _DeltaTime;

	if (OverlapTime < 0.2f)
	{
		return;
	}

	if (true == GameEngineInput::IsDown("SelectMoveRight"))
	{
		if (DelayTime < OverlapTime)
		{
			if (GetPos().ix() == SelectMenu_Button_Start::StartB->GetPos().ix())
			{
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_move.wav");
				BGMPlayer.Volume(0.1f);
				BGMPlayer.LoopCount(1);
				SetPos(SelectMenu_Button_Test::TestB->GetPos());
				OverlapTime = 0.0;
			}
		}
		if (DelayTime < OverlapTime)
		{
			if (GetPos().ix() == SelectMenu_Button_Test::TestB->GetPos().ix())
			{
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_move.wav");
				BGMPlayer.Volume(0.1f);
				BGMPlayer.LoopCount(1);
				SetPos(SelectMenu_Button_End::EndB->GetPos());
				OverlapTime = 0.0;
			}
		}
		if (DelayTime < OverlapTime)
		{
			if (GetPos().ix() == SelectMenu_Button_End::EndB->GetPos().ix())
			{
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_move.wav");
				BGMPlayer.Volume(0.1f);
				BGMPlayer.LoopCount(1);
				SetPos(SelectMenu_Button_Start::StartB->GetPos());
				OverlapTime = 0.0;
			}
		}
	}

	if (true == GameEngineInput::IsDown("SelectMoveLeft"))
	{
		if (DelayTime < OverlapTime)
		{
			if (GetPos().ix() == SelectMenu_Button_Start::StartB->GetPos().ix())
			{
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_move.wav");
				BGMPlayer.Volume(0.1f);
				BGMPlayer.LoopCount(1);
				SetPos(SelectMenu_Button_End::EndB->GetPos());
				OverlapTime = 0.0;
			}
		}
		if (DelayTime < OverlapTime)
		{
			if (GetPos().ix() == SelectMenu_Button_Test::TestB->GetPos().ix())
			{
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_move.wav");
				BGMPlayer.Volume(0.1f);
				BGMPlayer.LoopCount(1);
				SetPos(SelectMenu_Button_Start::StartB->GetPos());
				OverlapTime = 0.0;
			}
		}
		if (DelayTime < OverlapTime)
		{
			if (GetPos().ix() == SelectMenu_Button_End::EndB->GetPos().ix())
			{
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_move.wav");
				BGMPlayer.Volume(0.1f);
				BGMPlayer.LoopCount(1);
				SetPos(SelectMenu_Button_Test::TestB->GetPos());
				OverlapTime = 0.0;
			}
		}
	}


}