#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Machinegun_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	Machinegun_Background();
	~Machinegun_Background();

	// delete Function
	Machinegun_Background(const Machinegun_Background& _Other) = delete;
	Machinegun_Background(Machinegun_Background&& _Other) noexcept = delete;
	Machinegun_Background& operator=(const Machinegun_Background& _Other) = delete;
	Machinegun_Background& operator=(Machinegun_Background&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

