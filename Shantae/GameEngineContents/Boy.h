#pragma once

#include <GameEngineCore/GameEngineActor.h>

enum class BoyState
{
	IDLE,
	MOVE,
	RUN,
};

// ???? : Player Chracter
class Boy : public GameEngineActor
{
public:
	// constrcuter destructer
	Boy();
	~Boy();

	// delete Function
	Boy(const Boy& _Other) = delete;
	Boy(Boy&& _Other) noexcept = delete;
	Boy& operator=(const Boy& _Other) = delete;
	Boy& operator=(Boy&& _Other) noexcept = delete;

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

	bool MoveDirect = true; // true = Left, false = Right
	bool IsRun = false;
	bool IsTurn = false;

	// State
	std::string DirString = "_L";
	BoyState StateValue = BoyState::IDLE;

	void ChangeState(BoyState _State);
	void UpdateState(float _Time);
	std::string DirCheck(const std::string_view& _AnimationName);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	void RunStart();
	void RunUpdate(float _Time);
	void RunEnd();

};

