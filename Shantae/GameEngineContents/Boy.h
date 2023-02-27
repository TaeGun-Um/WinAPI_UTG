#pragma once

#include <GameEngineCore/GameEngineActor.h>

enum class BoyState
{
	IDLE,
	MOVE,
	TURN,
	RUN,
};

// Ό³Έν : Player Chracter
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
	BoyState StateValue = BoyState::IDLE;

	void ChangeState(BoyState _State);
	void UpdateState(float _Time);
	std::string DirCheck(const std::string_view& _AnimationName);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

};

