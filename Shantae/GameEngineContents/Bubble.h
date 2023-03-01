#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class Bubble : public GameEngineActor
{
public:
	// constrcuter destructer
	Bubble();
	~Bubble();

	// delete Function
	Bubble(const Bubble& _Other) = delete;
	Bubble(Bubble&& _Other) noexcept = delete;
	Bubble& operator=(const Bubble& _Other) = delete;
	Bubble& operator=(Bubble&& _Other) noexcept = delete;

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

	GameEngineSoundPlayer BGMPlayer;

	int SoundCount = 1;
};

