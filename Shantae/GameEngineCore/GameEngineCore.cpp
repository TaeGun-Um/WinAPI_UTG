
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "GameEngineCore.h"
#include "GameEngineLevel.h"
#include "GameEngineResources.h"

GameEngineCore* Core;

// Core 리턴
GameEngineCore* GameEngineCore::GetInst()
{
	return Core;
}

// Core 생성과 동시에 릭체크, 업캐스팅
GameEngineCore::GameEngineCore()
{
	GameEngineDebug::LeakCheck();
	Core = this;
}

GameEngineCore::~GameEngineCore()
{
	std::map<std::string, GameEngineLevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = Levels.end();

	// 동적할당 해제
	for (size_t i = 0; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
		}
	}
	Levels.clear();
}

// 윈도우 창 생성, 프로그램 시작
void GameEngineCore::CoreStart(HINSTANCE _instance)
{
	GameEngineWindow::WindowCreate(_instance, "Shantae_WinAPI", { 1280, 720 }, { 0, 0 });
	GameEngineWindow::WindowLoop(GameEngineCore::GlobalStart, GameEngineCore::GlobalUpdate, GameEngineCore::GlobalEnd);
}

// WindowLoop->Start()
void GameEngineCore::GlobalStart()
{
	Core->Start();                         // CreateLevel
	// GameEngineInput::MouseCursorOff();  // 0208 : 윈도우창 내 마우스 커서 감추기
	GameEngineTime::GlobalTime.Reset();    // DeltaTime 생성
}

// WindowLoop->Update()
void GameEngineCore::GlobalUpdate()
{
	GameEngineSound::SoundUpdate();                      // 사운드 확인 후 재생
	float Time = GameEngineTime::GlobalTime.TimeCheck(); // 한 프레임(Loop 1회)의 Deltatime Check
	GameEngineInput::Update(Time);                       // 이전 프레임의 키 상태 확인

	// Level Change
	if (nullptr != Core->NextLevel)
	{
		GameEngineLevel* PrevLevel = Core->MainLevel;
		GameEngineLevel* NextLevel = Core->NextLevel;

		if (nullptr != PrevLevel)
		{
			PrevLevel->LevelChangeEnd(NextLevel);
		}

		Core->MainLevel = NextLevel;
		Core->NextLevel = nullptr;

		if (nullptr != NextLevel)
		{
			NextLevel->LevelChangeStart(PrevLevel);
		}
	}

	// 델타타임이 심하게 오버되는 현상 저지용
	// 온라인에서는 델타타임 제한에 문제가 발생할 위험이 크다.
	// 하지만, 싱글 플레이 게임이기 때문에 해당 형식은 괜찮을 수도 있다.
	if (1.0f / 60.0f <= Time)
	{
		Time = 1.0f / 60.0f;
	}

	Core->Update();

	if (nullptr == Core->MainLevel)
	{
		MsgAssert("레벨을 지정해주지 않은 상태로 코어를 실행했습니다");
		return;
	}

	Core->MainLevel->Update(Time);          // Level change, Actor의 상태 변화(Death) Check
	Core->MainLevel->ActorsUpdate(Time);    // Level 내 Actors Position Setting
	GameEngineWindow::DoubleBufferClear();  // 윈도우(창) clear
	Core->MainLevel->ActorsRender(Time);    // Level 내 Actors Image Rendering
	GameEngineWindow::DoubleBufferRender(); // 윈도우(창) 백버퍼에 update된 빈버퍼 Bitcopy
	Core->MainLevel->Release();             // Collision 상호작용 후 해당 구조를 통하여 메모리에서 정리(소거하는 구조)
}

// WindowLoop->End()
void GameEngineCore::GlobalEnd()
{
	Core->End();
	GameEngineResources::GetInst().Release();
}

// 윈도우(창)에 데이터를 표현할 Level 선택
void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = Levels.find(_Name.data());

	if (FindIter == Levels.end())
	{
		std::string Name = _Name.data();
		MsgAssert(Name + "존재하지 않는 레벨을 실행시키려고 했습니다");
		return;
	}

	NextLevel = FindIter->second;
}

// 동적할당된 Level에 data 입력
void GameEngineCore::LevelLoading(GameEngineLevel* _Level, const std::string_view& _Name)
{
	if (nullptr == _Level)
	{
		MsgAssert("nullptr 인 레벨을 로딩하려고 했습니다.");
		return;
	}

	_Level->SetName(_Name); // 0208~0209 SetName;
	_Level->Loading();      // Level에 data 입력
}