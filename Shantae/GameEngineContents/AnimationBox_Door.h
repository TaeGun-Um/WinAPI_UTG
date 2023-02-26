#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class AnimationBox_Door : public GameEngineActor
{
public:
	// constrcuter destructer
	AnimationBox_Door();
	~AnimationBox_Door();

	// delete Function
	AnimationBox_Door(const AnimationBox_Door& _Other) = delete;
	AnimationBox_Door(AnimationBox_Door&& _Other) noexcept = delete;
	AnimationBox_Door& operator=(const AnimationBox_Door& _Other) = delete;
	AnimationBox_Door& operator=(AnimationBox_Door&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void CollisionCheck();

	GameEngineCollision* BodyCollision = nullptr;

};

