#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Machinegun_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	Machinegun_Sky();
	~Machinegun_Sky();

	// delete Function
	Machinegun_Sky(const Machinegun_Sky& _Other) = delete;
	Machinegun_Sky(Machinegun_Sky&& _Other) noexcept = delete;
	Machinegun_Sky& operator=(const Machinegun_Sky& _Other) = delete;
	Machinegun_Sky& operator=(Machinegun_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

