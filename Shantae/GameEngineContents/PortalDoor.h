#pragma once

#include <GameEngineCore/GameEngineActor.h>

enum class PortalType
{
	TestRoom,
	TestRoom2,
	UncleRoom,
	Shop,
	Spa,
	Smith,
	SkyRoom,
	SaveRoom,
};

// Ό³Έν :
class PortalDoor : public GameEngineActor
{
public:
	// constrcuter destructer
	PortalDoor();
	~PortalDoor();

	// delete Function
	PortalDoor(const PortalDoor& _Other) = delete;
	PortalDoor(PortalDoor&& _Other) noexcept = delete;
	PortalDoor& operator=(const PortalDoor& _Other) = delete;
	PortalDoor& operator=(PortalDoor&& _Other) noexcept = delete;

	void SetPortalValue(PortalType _Value)
	{
		PortalValue = _Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void PortalCheck(float _DeltaTime);
	void Portal();

	GameEngineCollision* BodyCollision = nullptr;

	PortalType PortalValue = PortalType::TestRoom;

	bool IsPortal = false;
	bool IsPortalIn = false;

	int Por = 0;
};

