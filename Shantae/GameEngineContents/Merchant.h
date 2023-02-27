#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Merchant : public GameEngineActor
{
public:
	// constrcuter destructer
	Merchant();
	~Merchant();

	// delete Function
	Merchant(const Merchant& _Other) = delete;
	Merchant(Merchant&& _Other) noexcept = delete;
	Merchant& operator=(const Merchant& _Other) = delete;
	Merchant& operator=(Merchant&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Run();
	void CollisionCheck();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

};

