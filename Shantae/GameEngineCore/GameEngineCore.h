#pragma once

#include <map>
#include <string_view>
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>

class GameEngineLevel;

// ���� : �߻� Ŭ����. �������� map�� �����ص�.
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

	// Core ����
	static GameEngineCore* GetInst();

	// ������(â) ����, ���α׷� ����
	void CoreStart(HINSTANCE _instance);

	// ������(â)�� �����͸� ǥ���� Level ����
	void ChangeLevel(const std::string_view& _Name);

	// Render�� Image�� Actor Position Ȯ��
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
	virtual void Start() = 0;  // ����� Core�� Start ��, CreateLevel �ǽ�
	virtual void Update() = 0; // �̱���
	virtual void End() = 0;    // �̱���

	// Level ����(�����Ҵ�)
	template<typename LevelType>
	void CreateLevel(const std::string_view& _Name)
	{
		if (Levels.end() != Levels.find(_Name.data()))
		{
			std::string Name = _Name.data();
			MsgAssert(Name + " �̹� �����ϴ� �̸��� ������ ������� �߽��ϴ�");
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

	std::map<std::string, GameEngineLevel*> Levels;                            // ��� Level���� ����
													                           
	GameEngineLevel* MainLevel = nullptr;                                      // ������(â)�� �����͸� ǥ���� Level
	GameEngineLevel* NextLevel = nullptr;                                      // ��ü�� Level

	void LevelLoading(GameEngineLevel* _Level, const std::string_view& _Name); // �����Ҵ�� Level�� data �Է�

	bool IsDebugValue = false;                                                 // Render�� Image�� Actor Position Ȯ��
};
