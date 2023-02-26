#pragma once

#include <GameEngineCore/GameEngineActor.h>

enum class PortalType
{
	TestRoom,
	TestRoom2,
};

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
	void PortalCheck(float _DeltaTime);
	void Portal(PortalType _Type);

	GameEngineCollision* BodyCollision = nullptr;

	PortalType PortalValue = PortalType::TestRoom;

	bool IsPortal = false;
	bool IsPortalIn = false;
};

