#pragma once

#include <GameEngineCore/GameEngineActor.h>

enum class SquidsmithState
{
	IDLE,
	TURN,
	ACTION,
};

// Ό³Έν : Player Chracter
class Squidsmith : public GameEngineActor
{
public:
	// constrcuter destructer
	Squidsmith();
	~Squidsmith();

	// delete Function
	Squidsmith(const Squidsmith& _Other) = delete;
	Squidsmith(Squidsmith&& _Other) noexcept = delete;
	Squidsmith& operator=(const Squidsmith& _Other) = delete;
	Squidsmith& operator=(Squidsmith&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CollisionCheck();
	void CharacterDirect();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	bool MoveDirect = true; // true = Left, false = Right

	// State
	std::string DirString = "_L";
	SquidsmithState StateValue = SquidsmithState::IDLE;

	void ChangeState(SquidsmithState _State);
	void UpdateState(float _Time);
	std::string DirCheck(const std::string_view& _AnimationName);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

};

