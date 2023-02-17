#pragma once

#include <GameEngineCore/GameEngineActor.h>

class GameEngineImage;

enum class Soldier_MachinegunState
{
	IDLE,
	TURN_L,
	FIRE_L,
	TURN_LB,
	FIRE_M,
	TURN_R,
	FIRE_R,
	TURN_RB,
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

	float AccTime = 0.0f;

	Soldier_MachinegunState StateValue = Soldier_MachinegunState::IDLE;

	void Fire();

	void RenderSet();

	void ChangeState(Soldier_MachinegunState _State);
	void UpdateState(float _Time);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void TurnLStart();
	void TurnLUpdate(float _Time);
	void TurnLEnd();

	void FireLStart();
	void FireLUpdate(float _Time);
	void FireLEnd();

	void TurnLBStart();
	void TurnLBUpdate(float _Time);
	void TurnLBEnd();

	void FireMStart();
	void FireMUpdate(float _Time);
	void FireMEnd();

	void TurnRStart();
	void TurnRUpdate(float _Time);
	void TurnREnd();

	void FireRStart();
	void FireRUpdate(float _Time);
	void FireREnd();

	void TurnRBStart();
	void TurnRBUpdate(float _Time);
	void TurnRBEnd();

};

