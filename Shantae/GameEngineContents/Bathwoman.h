#pragma once

#include <GameEngineCore/GameEngineActor.h>

class A_Button;

// Ό³Έν : Player Chracter
class Bathwoman : public GameEngineActor
{
public:
	// constrcuter destructer
	Bathwoman();
	~Bathwoman();

	// delete Function
	Bathwoman(const Bathwoman& _Other) = delete;
	Bathwoman(Bathwoman&& _Other) noexcept = delete;
	Bathwoman& operator=(const Bathwoman& _Other) = delete;
	Bathwoman& operator=(Bathwoman&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CollisionCheck();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	A_Button* AButton = nullptr;

	int CreateAButtion = 1;
};

