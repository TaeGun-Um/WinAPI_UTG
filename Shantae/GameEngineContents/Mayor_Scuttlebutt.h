#pragma once

#include <GameEngineCore/GameEngineActor.h>

enum class Mayor_ScuttlebuttState
{
	IDLE,
	TURN,
};

// Ό³Έν : Player Chracter
class Mayor_Scuttlebutt : public GameEngineActor
{
public:
	// constrcuter destructer
	Mayor_Scuttlebutt();
	~Mayor_Scuttlebutt();

	// delete Function
	Mayor_Scuttlebutt(const Mayor_Scuttlebutt& _Other) = delete;
	Mayor_Scuttlebutt(Mayor_Scuttlebutt&& _Other) noexcept = delete;
	Mayor_Scuttlebutt& operator=(const Mayor_Scuttlebutt& _Other) = delete;
	Mayor_Scuttlebutt& operator=(Mayor_Scuttlebutt&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CharacterDirect();

	GameEngineRender* AnimationRender = nullptr;
	bool MoveDirect = true; // true = Left, false = Right

	// State
	std::string DirString = "_L";
	Mayor_ScuttlebuttState StateValue = Mayor_ScuttlebuttState::IDLE;

	void ChangeState(Mayor_ScuttlebuttState _State);
	void UpdateState(float _Time);
	std::string DirCheck(const std::string_view& _AnimationName);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

};

