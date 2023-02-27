#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Squidsmith : public GameEngineActor
{
public:
	// constrcuter destructer
	Squidsmith();
	~Squidsmith();

	// delete Function
	Squidsmith(const Squidsmith& _Other) = delete;
	Squidsmith(Squidsmith&& _Other) noexcept = delete;
	Squidsmith& operator=(const Squidsmith& _Other) = delete;
	Squidsmith& operator=(Squidsmith&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CollisionCheck();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;


};

