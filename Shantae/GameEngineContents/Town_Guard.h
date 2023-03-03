#pragma once

#include <GameEngineCore/GameEngineActor.h>

enum class Town_GuardState
{
	IDLE,
	TURN,
};

class A_Button;

// Ό³Έν : Player Chracter
class Town_Guard : public GameEngineActor
{
public:
	// constrcuter destructer
	Town_Guard();
	~Town_Guard();

	// delete Function
	Town_Guard(const Town_Guard& _Other) = delete;
	Town_Guard(Town_Guard&& _Other) noexcept = delete;
	Town_Guard& operator=(const Town_Guard& _Other) = delete;
	Town_Guard& operator=(Town_Guard&& _Other) noexcept = delete;

	void SetTownGuard()
	{
		PassGuard = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CollisionCheck();
	void CharacterDirect();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	A_Button* AButton = nullptr;

	bool MoveDirect = true; // true = Left, false = Right
	bool Isturn = false;
	bool PassGuard = false;

	int CreateAButtion = 1;

	// State
	std::string DirString = "_L";
	Town_GuardState StateValue = Town_GuardState::IDLE;

	void ChangeState(Town_GuardState _State);
	void UpdateState(float _Time);
	std::string DirCheck(const std::string_view& _AnimationName);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void TurnStart();
	void TurnUpdate(float _Time);
	void TurnEnd();
};

