#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Building2 : public GameEngineActor
{
public:
	// constrcuter destructer
	Building2();
	~Building2();

	// delete Function
	Building2(const Building2& _Other) = delete;
	Building2(Building2&& _Other) noexcept = delete;
	Building2& operator=(const Building2& _Other) = delete;
	Building2& operator=(Building2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CollisionCheck();
	void BuildingBreak(float _DeltaTime);
	void MoveCalculation(float _DeltaTime);
	void DirectCheckForKill();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	float4 InitPos = float4::Zero;
	float4 MoveDir = float4::Zero;

	float MoveSpeed = 250.0f;
	float B = 0.0f;
	float BTime = 0.0f;
	float BreakDelay = 0.0f;

	int InitCount = 1;

	bool Break = false;
};

