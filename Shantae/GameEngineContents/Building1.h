#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Building1 : public GameEngineActor
{
public:
	// constrcuter destructer
	Building1();
	~Building1();

	// delete Function
	Building1(const Building1& _Other) = delete;
	Building1(Building1&& _Other) noexcept = delete;
	Building1& operator=(const Building1& _Other) = delete;
	Building1& operator=(Building1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CollisionCheck();
	void MoveCalculation(float _DeltaTime);

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	float MoveSpeed = 250.0f;
};

