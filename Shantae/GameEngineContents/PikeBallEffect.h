#pragma once

#include <GameEngineCore/GameEngineActor.h>

class Player;

// Ό³Έν : Player Chracter
class PikeBallEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	PikeBallEffect();
	~PikeBallEffect();

	// delete Function
	PikeBallEffect(const PikeBallEffect& _Other) = delete;
	PikeBallEffect(PikeBallEffect&& _Other) noexcept = delete;
	PikeBallEffect& operator=(const PikeBallEffect& _Other) = delete;
	PikeBallEffect& operator=(PikeBallEffect&& _Other) noexcept = delete;

	void Kill();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void MoveCalculation(float _DeltaTime);

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	float4 PivotPoint = float4::Zero;
	float4 NewPos = float4::Zero;
	float Angle = 0.0f;
	float RotationTime = 0.0f;


	int PivotSet = 1;
};

