#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>

enum class SquidsmithState
{
	IDLE,
	TURN,
	ACTION,
};

class A_Button;

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

	void PlayHeartAction()
	{
		HeartAction = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CollisionCheck();
	void CharacterDirect();

	GameEngineSoundPlayer BGMPlayer;

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	A_Button* AButton = nullptr;

	bool MoveDirect = true; // true = Left, false = Right
	bool Isturn = false;
	bool HeartAction = false;

	int CreateAButtion = 1;
	int ActionSoundCount = 1;

	// State
	std::string DirString = "_L";
	SquidsmithState StateValue = SquidsmithState::IDLE;

	void ChangeState(SquidsmithState _State);
	void UpdateState(float _Time);
	std::string DirCheck(const std::string_view& _AnimationName);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void TurnStart();
	void TurnUpdate(float _Time);
	void TurnEnd();

	void ActionStart();
	void ActionUpdate(float _Time);
	void ActionEnd();

};
