#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Stair_Bush2 : public GameEngineActor
{
public:
	// constrcuter destructer
	Stair_Bush2();
	~Stair_Bush2();

	// delete Function
	Stair_Bush2(const Stair_Bush2& _Other) = delete;
	Stair_Bush2(Stair_Bush2&& _Other) noexcept = delete;
	Stair_Bush2& operator=(const Stair_Bush2& _Other) = delete;
	Stair_Bush2& operator=(Stair_Bush2&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

