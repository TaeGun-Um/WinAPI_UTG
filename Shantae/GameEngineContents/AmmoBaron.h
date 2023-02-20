#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class GameEngineImage;

enum class AmmoBaronState
{
	FLY,
	DOWN,
	STRUGGLE,
	STANDUP,
	DUSTOFF,
	RUN,
	JUMP,
	IDLE,
	MOVE,
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

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

	void SetBaronAction()
	{
		IsAction = true;
	}

	bool GetBaronAction()
	{
		return IsAction;
	}

	int GetBaronHP()
	{
		return BaronHP;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void RenderSet();
	void CollisionSet();
	void CollisionCheck();
	void MoveCalculation(float _DeltaTime);

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;

	float MoveSpeed = 0.0f;
	float DowningTime = 0.0f;
	float StruggleTime = 0.0f;

	int BaronHP = 50;

	bool IsAction = false;
	bool IsStart = false;
	bool IsTurn = false;

	AmmoBaronState StateValue = AmmoBaronState::IDLE;
	void ChangeState(AmmoBaronState _State);
	void UpdateState(float _Time);

	void FlyStart();
	void FlyUpdate(float _DeltaTime);
	void FlyEnd();

	void DownStart();
	void DownUpdate(float _DeltaTime);
	void DownEnd();

	void StruggleStart();
	void StruggleUpdate(float _DeltaTime);
	void StruggleEnd();

	void StandupStart();
	void StandupUpdate(float _DeltaTime);
	void StandupEnd();

	void DustoffStart();
	void DustoffUpdate(float _DeltaTime);
	void DustoffEnd();

	void RunStart();
	void RunUpdate(float _DeltaTime);
	void RunEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

};

