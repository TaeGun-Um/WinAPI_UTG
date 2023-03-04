#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class Wavesplash : public GameEngineActor
{
public:
	// constrcuter destructer
	Wavesplash();
	~Wavesplash();

	// delete Function
	Wavesplash(const Wavesplash& _Other) = delete;
	Wavesplash(Wavesplash&& _Other) noexcept = delete;
	Wavesplash& operator=(const Wavesplash& _Other) = delete;
	Wavesplash& operator=(Wavesplash&& _Other) noexcept = delete;

	void SetScale(float4 _Scale)
	{
		BodyCollision->SetScale(_Scale);
	}

	void SetHealthWater()
	{
		IsHelthWater = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineSoundPlayer BGMPlayer;
	
	void CreateSplash();
	void CollisionCheck();
	void HealthWater(float _DeltaTime);

	float HealTiem = 0.0f;

	int CreateSpl = 1;

	bool IsIn = false;
	bool IsHelthWater = false;

};
