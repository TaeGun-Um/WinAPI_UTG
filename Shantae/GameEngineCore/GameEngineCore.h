#pragma once

#include <map>
#include <string_view>
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>

class GameEngineLevel;

// 설명 : 추상 클래스. 레벨들을 map에 저장해둠.
class GameEngineCore
{
public:
	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	// Core 리턴
	static GameEngineCore* GetInst();

	// 윈도우(창) 생성, 프로그램 실행
	void CoreStart(HINSTANCE _instance);

	// 윈도우(창)에 데이터를 표현할 Level 선택
	void ChangeLevel(const std::string_view& _Name);

	// Render된 Image의 Actor Position 확인
	void DebugSwitch()
	{
		IsDebugValue = !IsDebugValue;
	}

	void SetDebugMode(bool _IsDebug)
	{
		IsDebugValue = _IsDebug;
	}

	bool IsDebug()
	{
		return IsDebugValue;
	}

protected:
	virtual void Start() = 0;  // 상속한 Core의 Start 콜, CreateLevel 실시
	virtual void Update() = 0; // 미구현
	virtual void End() = 0;    // 미구현

	// Level 생성(동적할당)
	template<typename LevelType>
	void CreateLevel(const std::string_view& _Name)
	{
		if (Levels.end() != Levels.find(_Name.data()))
		{
			std::string Name = _Name.data();
			MsgAssert(Name + " 이미 존재하는 이름의 레벨을 만들려고 했습니다");
			return;
		}

		GameEngineLevel* Level = new LevelType();
		LevelLoading(Level, _Name);
		Levels.insert(std::make_pair(_Name.data(), Level));
	}

private:
	static void GlobalStart();  // WindowLoop->Start()
	static void GlobalUpdate(); // WindowLoop->Update()
	static void GlobalEnd();    // WindowLoop->End()

	std::map<std::string, GameEngineLevel*> Levels;                            // 모든 Level들의 정보
													                           
	GameEngineLevel* MainLevel = nullptr;                                      // 윈도우(창)에 데이터를 표현할 Level
	GameEngineLevel* NextLevel = nullptr;                                      // 교체될 Level

	void LevelLoading(GameEngineLevel* _Level, const std::string_view& _Name); // 동적할당된 Level에 data 입력

	bool IsDebugValue = false;                                                 // Render된 Image의 Actor Position 확인
};
