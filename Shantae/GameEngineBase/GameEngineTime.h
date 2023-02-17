#pragma once

#include <Windows.h>

// 설명 : 시간을 재는 기능들을 담당
class GameEngineTime
{
public:
	static GameEngineTime GlobalTime;

	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	// Prev 갱신
	void Reset();

	// Current 갱신, DeltaTime 계산 후 리턴
	float TimeCheck();

	// DeltaTime 리턴
	inline float GetFloatDeltaTime() const
	{
		return floatDeltaTime;
	}

protected:

private:
	LARGE_INTEGER Prev     = LARGE_INTEGER(); // GameEngineTime 생성, Reset 호출 시점의 진동횟수
	LARGE_INTEGER Current  = LARGE_INTEGER(); // TimeCheck 호출 시점의 진동횟수
	LARGE_INTEGER Second   = LARGE_INTEGER(); // CPU 1초당 진동횟수

	double DoubleDeltaTime = 0.0;             // Current(진동횟수) - Prev(진동횟수) / Second(진동횟수)
	float floatDeltaTime   = 0.0;             // DoubleDeltaTime을 float으로 변환한 값

	__int64 Tick           = 0;
};

