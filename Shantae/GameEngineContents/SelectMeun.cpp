#include "SelectMeun.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "SelectMenu_Background.h"
#include "SelectMenu_Button_Start.h"
#include "SelectMenu_Button_Test.h"
#include "SelectMenu_Button_End.h"
#include "SelectMenu_Icon.h"

SelectMeun::SelectMeun() 
{
}

SelectMeun::~SelectMeun() 
{
}

void SelectMeun::Loading()
{
	// 이거 빼고 다 지워도 됨(0130, 0201 주석은 수업에서 활용한 것)
	CreateActor<SelectMenu_Background>();
	CreateActor<SelectMenu_Button_Start>();
	CreateActor<SelectMenu_Button_Test>();
	CreateActor<SelectMenu_Button_End>();
	CreateActor<SelectMenu_Icon>();

	// 0201
	Start = float4::Zero;
	End = float4(0.0f, GameEngineWindow::GetScreenSize().half().y);
}

// 0130
bool ScrollStart = false;
float4 DownPosTitle = float4::Zero;

void SelectMeun::Update(float _DeltaTime)
{
	// 0130
	//if (true == GameEngineInput::IsDown("TitleScroll"))
	//{
	//	ScrollStart = true;
	//}
	// 0130 선형보간 미적용시
	//if (true == ScrollStart)
	//{
	//	DownPosTitle += float4::Down * 100.0f * _DeltaTime;

	//	SetCameraMove(float4::Down * 100.0f * _DeltaTime);

	//	if (GameEngineWindow::GetScreenSize().half().y <= DownPosTitle.y)
	//	{
	//		DownPosTitle.y = GameEngineWindow::GetScreenSize().half().y;
	//		SetCameraPos(DownPosTitle);
	//		ScrollStart = false;
	//	}
	//}

	// 0201 선형보간 적용 예시
	//if (false == ScrollStart)
	//{
	//	if (true == GameEngineInput::IsDown("TitleScrollLeft"))
	//	{
	//		End = Start + float4(-GameEngineWindow::GetScreenSize().half().x, 0.0f);
	//		ScrollStart = true;
	//	}
	//	else if (true == GameEngineInput::IsDown("TitleScrollRight"))
	//	{
	//		End = Start + float4(GameEngineWindow::GetScreenSize().half().x, 0.0f);
	//		ScrollStart = true;
	//	}
	//	else if (true == GameEngineInput::IsDown("TitleScrollUp"))
	//	{
	//		End = Start + float4(0.0f, GameEngineWindow::GetScreenSize().half().y);
	//		ScrollStart = true;
	//	}
	//	else if (true == GameEngineInput::IsDown("TitleScrollDown"))
	//	{
	//		End = Start + float4(0.0f, -GameEngineWindow::GetScreenSize().half().y);
	//		ScrollStart = true;
	//	}
	//}
	//if (true == ScrollStart)
	//{
	//	// 시작에서 끝까지 이동하는데 1초가 걸리는 함수
	//	Time += _DeltaTime * 0.5f;
	//	float4 Pos = float4::LerpClamp(Start, End, Time);
	//	SetCameraPos(Pos);

	//	if (Time >= 1.0f)
	//	{
	//		ScrollStart = false;
	//		Time = 0.0f;
	//		Start = Pos;
	//	}
	//}
}

void SelectMeun::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("File_Select.mp3");
	BGMPlayer.Volume(0.08f);
	BGMPlayer.LoopCount(10);
}

void SelectMeun::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}