#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestRoomMap2 : public GameEngineActor
{
public:
	// constrcuter destructer
	TestRoomMap2();
	~TestRoomMap2();

	// delete Function
	TestRoomMap2(const TestRoomMap2& _Other) = delete;
	TestRoomMap2(TestRoomMap2&& _Other) noexcept = delete;
	TestRoomMap2& operator=(const TestRoomMap2& _Other) = delete;
	TestRoomMap2& operator=(TestRoomMap2&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

