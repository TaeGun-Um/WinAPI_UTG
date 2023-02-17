#pragma once

#include <GameEngineCore/GameEngineActor.h>

class GameEngineImage;

enum class Soldier_MachinegunState
{
	MOVE,
	HIT,
};

// Ό³Έν : Player Chracter
class Soldier_Machinegun : public GameEngineActor
{
public:
	// constrcuter destructer
	Soldier_Machinegun();
	~Soldier_Machinegun();

	// delete Function
	Soldier_Machinegun(const Soldier_Machinegun& _Other) = delete;
	Soldier_Machinegun(Soldier_Machinegun&& _Other) noexcept = delete;
	Soldier_Machinegun& operator=(const Soldier_Machinegun& _Other) = delete;
	Soldier_Machinegun& operator=(Soldier_Machinegun&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

