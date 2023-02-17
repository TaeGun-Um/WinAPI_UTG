#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Stair_Bush1 : public GameEngineActor
{
public:
	// constrcuter destructer
	Stair_Bush1();
	~Stair_Bush1();

	// delete Function
	Stair_Bush1(const Stair_Bush1& _Other) = delete;
	Stair_Bush1(Stair_Bush1&& _Other) noexcept = delete;
	Stair_Bush1& operator=(const Stair_Bush1& _Other) = delete;
	Stair_Bush1& operator=(Stair_Bush1&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

