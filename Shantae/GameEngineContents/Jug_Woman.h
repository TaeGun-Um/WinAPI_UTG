#pragma once

#include <GameEngineCore/GameEngineActor.h>

enum class Jug_WomanState
{
	IDLE,
	MOVE,
	TURN,
	RUN,
};

// Ό³Έν : Player Chracter
class Jug_Woman : public GameEngineActor
{
public:
	// constrcuter destructer
	Jug_Woman();
	~Jug_Woman();

	// delete Function
	Jug_Woman(const Jug_Woman& _Other) = delete;
	Jug_Woman(Jug_Woman&& _Other) noexcept = delete;
	Jug_Woman& operator=(const Jug_Woman& _Other) = delete;
	Jug_Woman& operator=(Jug_Woman&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DirectCheckForKill();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;

	float4 CurrentPos = float4::Zero;

	int CurrentPosCount = 1;

	bool MoveDirect = true; // true = Left, false = Right
	bool IsRun = false;

	// State
	std::string DirString = "_L";
	Jug_WomanState StateValue = Jug_WomanState::IDLE;

	void ChangeState(Jug_WomanState _State);
	void UpdateState(float _Time);
	std::string DirCheck(const std::string_view& _AnimationName);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

};

