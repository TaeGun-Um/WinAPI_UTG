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
	OverlapTime += _DeltaTime;

	if (OverlapTime < 0.2f)
	{
		return;
	}

	if (true == GameEngineInput::IsPress("SelectMoveRight"))
	{
		if (DelayTime < OverlapTime)
		{
			if (GetPos().ix() == SelectMenu_Button_Start::StartB->GetPos().ix())
			{
				SetPos(SelectMenu_Button_Test::TestB->GetPos());
				OverlapTime = 0.0;
			}
		}
		if (DelayTime < OverlapTime)
		{
			if (GetPos().ix() == SelectMenu_Button_Test::TestB->GetPos().ix())
			{
				SetPos(SelectMenu_Button_End::EndB->GetPos());
				OverlapTime = 0.0;
			}
		}
		if (DelayTime < OverlapTime)
		{
			if (GetPos().ix() == SelectMenu_Button_End::EndB->GetPos().ix())
			{
				SetPos(SelectMenu_Button_Start::StartB->GetPos());
				OverlapTime = 0.0;
			}
		}
	}

	if (true == GameEngineInput::IsPress("SelectMoveLeft"))
	{
		if (DelayTime < OverlapTime)
		{
			if (GetPos().ix() == SelectMenu_Button_Start::StartB->GetPos().ix())
			{
				SetPos(SelectMenu_Button_End::EndB->GetPos());
				OverlapTime = 0.0;
			}
		}
		if (DelayTime < OverlapTime)
		{
			if (GetPos().ix() == SelectMenu_Button_Test::TestB->GetPos().ix())
			{
				SetPos(SelectMenu_Button_Start::StartB->GetPos());
				OverlapTime = 0.0;
			}
		}
		if (DelayTime < OverlapTime)
		{
			if (GetPos().ix() == SelectMenu_Button_End::EndB->GetPos().ix())
			{
				SetPos(SelectMenu_Button_Test::TestB->GetPos());
				OverlapTime = 0.0;
			}
		}
	}

	if (true == GameEngineInput::IsPress("Select"))
	{
		if (GetPos().ix() == SelectMenu_Button_Start::StartB->GetPos().ix())
		{
			GameEngineCore::GetInst()->ChangeLevel("House");
		}
		if (GetPos().ix() == SelectMenu_Button_Test::TestB->GetPos().ix())
		{
			GameEngineCore::GetInst()->ChangeLevel("TestLevel");
		}
		if (GetPos().ix() == SelectMenu_Button_End::EndB->GetPos().ix())
		{
			GameEngineWindow::AppOff();
		}
	}
}