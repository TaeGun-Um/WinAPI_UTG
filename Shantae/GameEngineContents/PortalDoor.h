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

class BlackBox;
class Up_Button;

// Ό³Έν :
class PortalDoor : public GameEngineActor
{
public:
	static BlackBox* BBox;
	static int BBoxCount;

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
	void BlackBoxInAnimation();
	void InBoxKill();
	void PortalCheck(float _DeltaTime);
	void Portal();

	GameEngineCollision* BodyCollision = nullptr;
	Up_Button* UpButton = nullptr;

	PortalType PortalValue = PortalType::TestRoom;

	bool IsPortal = false;
	bool IsPortalIn = false;

	int Por = 0;
	int CreateUpButtion = 1;
};

