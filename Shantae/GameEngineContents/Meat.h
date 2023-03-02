#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class Meat : public GameEngineActor
{
public:
	// constrcuter destructer
	Meat();
	~Meat();

	// delete Function
	Meat(const Meat& _Other) = delete;
	Meat(Meat&& _Other) noexcept = delete;
	Meat& operator=(const Meat& _Other) = delete;
	Meat& operator=(Meat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void MoveCalculation(float _DeltaTime);
	void CollisionCheck(float _DeltaTime);
	void ApplyScore();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	float4 UpPos = float4::Zero;

	GameEngineSoundPlayer BGMPlayer;

	int SoundCount = 1;
	int UpCount = 1;

	bool IsUp = false;

};

