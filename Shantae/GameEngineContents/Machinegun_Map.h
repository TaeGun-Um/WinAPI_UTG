#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Machinegun_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Machinegun_Map();
	~Machinegun_Map();

	// delete Function
	Machinegun_Map(const Machinegun_Map& _Other) = delete;
	Machinegun_Map(Machinegun_Map&& _Other) noexcept = delete;
	Machinegun_Map& operator=(const Machinegun_Map& _Other) = delete;
	Machinegun_Map& operator=(Machinegun_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};
