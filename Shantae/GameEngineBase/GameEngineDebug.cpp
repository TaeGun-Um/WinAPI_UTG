#include <crtdbg.h>
#include "GameEngineDebug.h"

GameEngineDebug::GameEngineDebug()
{
}

GameEngineDebug::~GameEngineDebug()
{
}

void GameEngineDebug::LeakCheck()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

// 릭발생시 숫자는 릭이 발생한 구역 근방치를 알려주는 것
// debug에 LeakPointBreak 만들고 포인트에 릭발생시 숫자를 넣어줌, 다음으로 실행
// 위치가 정확하게 안나올 수 있으며, 실행하면 멈추니까 썼으면 지우면 됨
void GameEngineDebug::LeakPointBreak(int _Point)
{
	_CrtSetBreakAlloc(_Point);
}