#pragma once

#include <string>
#include <Windows.h>
#include <assert.h>

// 설명 : 매크로 함수, LeakCheck
class GameEngineDebug
{
public:

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

	static void LeakCheck();
	
	// 릭 발생시 뜨는 숫자를 입력한뒤 호출하면 해당 위치 부근으로 이동
	static void LeakPointBreak(int _Point);

protected:

private:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

};

// 매크로 함수
#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);