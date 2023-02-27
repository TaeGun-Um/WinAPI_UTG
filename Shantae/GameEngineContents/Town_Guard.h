#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Town_Guard : public GameEngineActor
{
public:
	// constrcuter destructer
	Town_Guard();
	~Town_Guard();

	// delete Function
	Town_Guard(const Town_Guard& _Other) = delete;
	Town_Guard(Town_Guard&& _Other) noexcept = delete;
	Town_Guard& operator=(const Town_Guard& _Other) = delete;
	Town_Guard& operator=(Town_Guard&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CollisionCheck();
	void DirCheck();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	bool MoveDirect = true; // true = Left, false = Right

};

