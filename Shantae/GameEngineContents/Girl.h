#pragma once

#include <GameEngineCore/GameEngineActor.h>

enum class GirlState
{
	IDLE,
	MOVE,
	TURN,
	RUN,
};

// Ό³Έν : Player Chracter
class Girl : public GameEngineActor
{
public:
	// constrcuter destructer
	Girl();
	~Girl();

	// delete Function
	Girl(const Girl& _Other) = delete;
	Girl(Girl&& _Other) noexcept = delete;
	Girl& operator=(const Girl& _Other) = delete;
	Girl& operator=(Girl&& _Other) noexcept = delete;

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
	GirlState StateValue = GirlState::IDLE;

	void ChangeState(GirlState _State);
	void UpdateState(float _Time);
	std::string DirCheck(const std::string_view& _AnimationName);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

};

