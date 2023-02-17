#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Stair_Stair : public GameEngineActor
{
public:
	// constrcuter destructer
	Stair_Stair();
	~Stair_Stair();

	// delete Function
	Stair_Stair(const Stair_Stair& _Other) = delete;
	Stair_Stair(Stair_Stair&& _Other) noexcept = delete;
	Stair_Stair& operator=(const Stair_Stair& _Other) = delete;
	Stair_Stair& operator=(Stair_Stair&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

