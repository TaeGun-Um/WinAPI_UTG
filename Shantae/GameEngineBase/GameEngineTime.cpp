#include "GameEngineTime.h"

GameEngineTime GameEngineTime::GlobalTime;

// ��ü ������ �Բ� �󵵼��� ȣ�� ���� ����
GameEngineTime::GameEngineTime()
{
	QueryPerformanceFrequency(&Second);
	QueryPerformanceCounter(&Prev);
}

GameEngineTime::~GameEngineTime()
{
}

// Prev ����
void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

// Current ����, DeltaTime ��� �� ����
float GameEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&Current);

	Tick = Current.QuadPart - Prev.QuadPart;

	// Deltatime ���
	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);

	// Prev ����
	Prev.QuadPart = Current.QuadPart;

	floatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return floatDeltaTime;
}
