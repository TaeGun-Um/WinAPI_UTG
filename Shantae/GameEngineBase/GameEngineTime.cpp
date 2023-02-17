#include "GameEngineTime.h"

GameEngineTime GameEngineTime::GlobalTime;

// 객체 생성과 함께 빈도수와 호출 시점 생성
GameEngineTime::GameEngineTime()
{
	QueryPerformanceFrequency(&Second);
	QueryPerformanceCounter(&Prev);
}

GameEngineTime::~GameEngineTime()
{
}

// Prev 갱신
void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

// Current 갱신, DeltaTime 계산 후 리턴
float GameEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&Current);

	Tick = Current.QuadPart - Prev.QuadPart;

	// Deltatime 계산
	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);

	// Prev 갱신
	Prev.QuadPart = Current.QuadPart;

	floatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return floatDeltaTime;
}
