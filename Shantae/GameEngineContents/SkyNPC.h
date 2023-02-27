#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class SkyNPC : public GameEngineActor
{
public:
	// constrcuter destructer
	SkyNPC();
	~SkyNPC();

	// delete Function
	SkyNPC(const SkyNPC& _Other) = delete;
	SkyNPC(SkyNPC&& _Other) noexcept = delete;
	SkyNPC& operator=(const SkyNPC& _Other) = delete;
	SkyNPC& operator=(SkyNPC&& _Other) noexcept = delete;

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

