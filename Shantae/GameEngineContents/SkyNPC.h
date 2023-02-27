#pragma once

#include <GameEngineCore/GameEngineActor.h>

enum class SkyNPCState
{
	IDLE,
	MOVE,
	TURN,
};

// Ό³Έν : Player Chracter
class SkyNPC : public GameEngineActor
{
public:
	// constrcuter destructer
	SkyNPC();
	~SkyNPC();

	// delete Function
	SkyNPC(const SkyNPC& _Other) = delete;
	SkyNPC(SkyNPC&& _Other) noexcept = delete;
	SkyNPC& operator=(const SkyNPC& _Other) = delete;
	SkyNPC& operator=(SkyNPC&& _Other) noexcept = delete;

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
	SkyNPCState StateValue = SkyNPCState::IDLE;

	void ChangeState(SkyNPCState _State);
	void UpdateState(float _Time);
	std::string DirCheck(const std::string_view& _AnimationName);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();
};

