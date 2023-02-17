#pragma once

#include <Windows.h>

// ���� : �ð��� ��� ��ɵ��� ���
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

	// Prev ����
	void Reset();

	// Current ����, DeltaTime ��� �� ����
	float TimeCheck();

	// DeltaTime ����
	inline float GetFloatDeltaTime() const
	{
		return floatDeltaTime;
	}

protected:

private:
	LARGE_INTEGER Prev     = LARGE_INTEGER(); // GameEngineTime ����, Reset ȣ�� ������ ����Ƚ��
	LARGE_INTEGER Current  = LARGE_INTEGER(); // TimeCheck ȣ�� ������ ����Ƚ��
	LARGE_INTEGER Second   = LARGE_INTEGER(); // CPU 1�ʴ� ����Ƚ��

	double DoubleDeltaTime = 0.0;             // Current(����Ƚ��) - Prev(����Ƚ��) / Second(����Ƚ��)
	float floatDeltaTime   = 0.0;             // DoubleDeltaTime�� float���� ��ȯ�� ��

	__int64 Tick           = 0;
};

