#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestRoomMap : public GameEngineActor
{
public:
	// constrcuter destructer
	TestRoomMap();
	~TestRoomMap();

	// delete Function
	TestRoomMap(const TestRoomMap& _Other) = delete;
	TestRoomMap(TestRoomMap&& _Other) noexcept = delete;
	TestRoomMap& operator=(const TestRoomMap& _Other) = delete;
	TestRoomMap& operator=(TestRoomMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

