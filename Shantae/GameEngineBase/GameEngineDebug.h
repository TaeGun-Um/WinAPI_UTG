#pragma once

#include <string>
#include <Windows.h>
#include <assert.h>

// ���� : ��ũ�� �Լ�, LeakCheck
class GameEngineDebug
{
public:

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

	static void LeakCheck();
	
	// �� �߻��� �ߴ� ���ڸ� �Է��ѵ� ȣ���ϸ� �ش� ��ġ �α����� �̵�
	static void LeakPointBreak(int _Point);

protected:

private:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

};

// ��ũ�� �Լ�
#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);