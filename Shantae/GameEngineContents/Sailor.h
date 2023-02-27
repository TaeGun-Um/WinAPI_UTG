#pragma once

#include <GameEngineCore/GameEngineActor.h>

enum class SailorState
{
	IDLE,
	TURN,
};

// Ό³Έν : Player Chracter
class Sailor : public GameEngineActor
{
public:
	// constrcuter destructer
	Sailor();
	~Sailor();

	// delete Function
	Sailor(const Sailor& _Other) = delete;
	Sailor(Sailor&& _Other) noexcept = delete;
	Sailor& operator=(const Sailor& _Other) = delete;
	Sailor& operator=(Sailor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CharacterDirect();

	GameEngineRender* AnimationRender = nullptr;

	bool MoveDirect = true; // true = Left, false = Right
	bool Isturn = false;

	// State
	std::string DirString = "_L";
	SailorState StateValue = SailorState::IDLE;

	void ChangeState(SailorState _State);
	void UpdateState(float _Time);
	std::string DirCheck(const std::string_view& _AnimationName);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void TurnStart();
	void TurnUpdate(float _Time);
	void TurnEnd();

};

