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

// ���߻��� ���ڴ� ���� �߻��� ���� �ٹ�ġ�� �˷��ִ� ��
// debug�� LeakPointBreak ����� ����Ʈ�� ���߻��� ���ڸ� �־���, �������� ����
// ��ġ�� ��Ȯ�ϰ� �ȳ��� �� ������, �����ϸ� ���ߴϱ� ������ ����� ��
void GameEngineDebug::LeakPointBreak(int _Point)
{
	_CrtSetBreakAlloc(_Point);
}