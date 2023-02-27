#pragma once

#include <GameEngineCore/GameEngineActor.h>

enum class StylistState
{
	IDLE,
	MOVE,
	TURN,
	RUN,
};

// Ό³Έν : Player Chracter
class Stylist : public GameEngineActor
{
public:
	// constrcuter destructer
	Stylist();
	~Stylist();

	// delete Function
	Stylist(const Stylist& _Other) = delete;
	Stylist(Stylist&& _Other) noexcept = delete;
	Stylist& operator=(const Stylist& _Other) = delete;
	Stylist& operator=(Stylist&& _Other) noexcept = delete;

	void SetRun()
	{
		IsRun = true;
	}

	void SetRunSpeed(float _Speed)
	{
		RunSpeed = _Speed;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DirectCheckForKill();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;

	float4 CurrentPos = float4::Zero;
	float4 LeftMovePos = float4::Zero;

	float MoveTime = 0.0f;
	float RunSpeed = 0.0f;

	int CurrentPosCount = 1;
	int Pass = 1;

	bool MoveDirect = true; // true = Left, false = Right
	bool IsRun = false;
	bool IsTurn = false;

	// State
	std::string DirString = "_L";
	StylistState StateValue = StylistState::IDLE;

	void ChangeState(StylistState _State);
	void UpdateState(float _Time);
	std::string DirCheck(const std::string_view& _AnimationName);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	void TurnStart();
	void TurnUpdate(float _Time);
	void TurnEnd();

	void RunStart();
	void RunUpdate(float _Time);
	void RunEnd();

};

