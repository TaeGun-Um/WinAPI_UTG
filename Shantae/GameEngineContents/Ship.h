#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Ship : public GameEngineActor
{
public:
	// constrcuter destructer
	Ship();
	~Ship();

	// delete Function
	Ship(const Ship& _Other) = delete;
	Ship(Ship&& _Other) noexcept = delete;
	Ship& operator=(const Ship& _Other) = delete;
	Ship& operator=(Ship&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void MoveCalculation(float _DeltaTime);

	GameEngineRender* AnimationRender = nullptr;
	float MoveSpeed = 250.0f;
};

