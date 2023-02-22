#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class GameEngineImage;
class Soldier_Aim;

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

	GameEngineSoundPlayer BGMPlayer;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	Soldier_Aim* Aim_L = nullptr;
	Soldier_Aim* Aim_M = nullptr;
	Soldier_Aim* Aim_R = nullptr;

	float AccTime = 0.0f;
	int FireCount = 1;
	int AimCount = 3;

	void RenderSet();

	// 0 = Left, 1 = Middle, 2 = Right
	void Fire(const int _Value); 
	void CreateAim(const int _Value);
	void AimKill(const int _Value);

	Soldier_MachinegunState StateValue = Soldier_MachinegunState::IDLE;
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

