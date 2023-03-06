#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

// Ό³Έν :
class TimerCollision : public GameEngineActor
{
public:
	static TimerCollision* Timer;

	static TimerCollision* GetTimer()
	{
		return Timer;
	}

	// constrcuter destructer
	TimerCollision();
	~TimerCollision();

	// delete Function
	TimerCollision(const TimerCollision& _Other) = delete;
	TimerCollision(TimerCollision&& _Other) noexcept = delete;
	TimerCollision& operator=(const TimerCollision& _Other) = delete;
	TimerCollision& operator=(TimerCollision&& _Other) noexcept = delete;

	float GetAccTime()
	{
		return AccTime;
	}

	int GetTimerSet()
	{
		return TimerSet;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) {}

private:
	GameEngineCollision* TimerSpot = nullptr;
	GameEngineRender* TextRender1 = nullptr;
	GameEngineRender* TextRender2 = nullptr;
	GameEngineRender* TextRender3 = nullptr;

	int TimerSet = 1;
	float AccTime = 0.0f;

	bool IsText = false;

	std::vector<std::string> SpawnerText;
	std::string MonsterTYPE = "TimerCollision";
	float4 BoxScale = { 150, 150 };

	void CollisionCheck();
	void PositionText();

};

