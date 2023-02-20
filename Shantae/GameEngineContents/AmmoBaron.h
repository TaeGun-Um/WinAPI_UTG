#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class GameEngineImage;

enum class AmmoBaronState
{
	FLY,
	DOWN,
	UP,
	RUN,
	JUMP,
};

// Ό³Έν : Player Chracter
class AmmoBaron : public GameEngineActor
{
public:
	// constrcuter destructer
	AmmoBaron();
	~AmmoBaron();

	// delete Function
	AmmoBaron(const AmmoBaron& _Other) = delete;
	AmmoBaron(AmmoBaron&& _Other) noexcept = delete;
	AmmoBaron& operator=(const AmmoBaron& _Other) = delete;
	AmmoBaron& operator=(AmmoBaron&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	void RenderSet();
	void CollisionSet();
	void CollisionCheck();
	void MoveCalculation(float _DeltaTime);

	AmmoBaronState StateValue = AmmoBaronState::FLY;
	void ChangeState(AmmoBaronState _State);
	void UpdateState(float _Time);

	void FlyStart();
	void FlyUpdate(float _DeltaTime);
	void FlyEnd();

	void DownStart();
	void DownUpdate(float _DeltaTime);
	void DownEnd();

	void UpStart();
	void UpUpdate(float _DeltaTime);
	void UpEnd();

	void RunStart();
	void RunUpdate(float _DeltaTime);
	void RunEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();

};

