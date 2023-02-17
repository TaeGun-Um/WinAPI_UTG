
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "GameEngineCore.h"
#include "GameEngineLevel.h"
#include "GameEngineResources.h"

GameEngineCore* Core;

// Core ����
GameEngineCore* GameEngineCore::GetInst()
{
	return Core;
}

// Core ������ ���ÿ� ��üũ, ��ĳ����
GameEngineCore::GameEngineCore()
{
	GameEngineDebug::LeakCheck();
	Core = this;
}

GameEngineCore::~GameEngineCore()
{
	std::map<std::string, GameEngineLevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = Levels.end();

	// �����Ҵ� ����
	for (size_t i = 0; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
		}
	}
	Levels.clear();
}

// ������ â ����, ���α׷� ����
void GameEngineCore::CoreStart(HINSTANCE _instance)
{
	GameEngineWindow::WindowCreate(_instance, "Shantae_WinAPI", { 1280, 720 }, { 0, 0 });
	GameEngineWindow::WindowLoop(GameEngineCore::GlobalStart, GameEngineCore::GlobalUpdate, GameEngineCore::GlobalEnd);
}

// WindowLoop->Start()
void GameEngineCore::GlobalStart()
{
	Core->Start();                         // CreateLevel
	// GameEngineInput::MouseCursorOff();  // 0208 : ������â �� ���콺 Ŀ�� ���߱�
	GameEngineTime::GlobalTime.Reset();    // DeltaTime ����
}

// WindowLoop->Update()
void GameEngineCore::GlobalUpdate()
{
	GameEngineSound::SoundUpdate();                      // ���� Ȯ�� �� ���
	float Time = GameEngineTime::GlobalTime.TimeCheck(); // �� ������(Loop 1ȸ)�� Deltatime Check
	GameEngineInput::Update(Time);                       // ���� �������� Ű ���� Ȯ��

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

	// ��ŸŸ���� ���ϰ� �����Ǵ� ���� ������
	// �¶��ο����� ��ŸŸ�� ���ѿ� ������ �߻��� ������ ũ��.
	// ������, �̱� �÷��� �����̱� ������ �ش� ������ ������ ���� �ִ�.
	if (1.0f / 60.0f <= Time)
	{
		Time = 1.0f / 60.0f;
	}

	Core->Update();

	if (nullptr == Core->MainLevel)
	{
		MsgAssert("������ ���������� ���� ���·� �ھ �����߽��ϴ�");
		return;
	}

	Core->MainLevel->Update(Time);          // Level change, Actor�� ���� ��ȭ(Death) Check
	Core->MainLevel->ActorsUpdate(Time);    // Level �� Actors Position Setting
	GameEngineWindow::DoubleBufferClear();  // ������(â) clear
	Core->MainLevel->ActorsRender(Time);    // Level �� Actors Image Rendering
	GameEngineWindow::DoubleBufferRender(); // ������(â) ����ۿ� update�� ����� Bitcopy
	Core->MainLevel->Release();             // Collision ��ȣ�ۿ� �� �ش� ������ ���Ͽ� �޸𸮿��� ����(�Ұ��ϴ� ����)
}

// WindowLoop->End()
void GameEngineCore::GlobalEnd()
{
	Core->End();
	GameEngineResources::GetInst().Release();
}

// ������(â)�� �����͸� ǥ���� Level ����
void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = Levels.find(_Name.data());

	if (FindIter == Levels.end())
	{
		std::string Name = _Name.data();
		MsgAssert(Name + "�������� �ʴ� ������ �����Ű���� �߽��ϴ�");
		return;
	}

	NextLevel = FindIter->second;
}

// �����Ҵ�� Level�� data �Է�
void GameEngineCore::LevelLoading(GameEngineLevel* _Level, const std::string_view& _Name)
{
	if (nullptr == _Level)
	{
		MsgAssert("nullptr �� ������ �ε��Ϸ��� �߽��ϴ�.");
		return;
	}

	_Level->SetName(_Name); // 0208~0209 SetName;
	_Level->Loading();      // Level�� data �Է�
}