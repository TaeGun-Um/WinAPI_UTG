#pragma once

#include <GameEngineCore/GameEngineActor.h>

class GameEngineImage;

enum class Boss_TankState
{
	IDLE,
	IDLEREV,
	MOVE,
	CHARGE,
	BACKUP,
	FIRE,
	HIT,
};

// Ό³Έν : Player Chracter
class Boss_Tank : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_Tank();
	~Boss_Tank();

	// delete Function
	Boss_Tank(const Boss_Tank& _Other) = delete;
	Boss_Tank(Boss_Tank&& _Other) noexcept = delete;
	Boss_Tank& operator=(const Boss_Tank& _Other) = delete;
	Boss_Tank& operator=(Boss_Tank&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	float4 BossPos = float4::Zero;
	float4 ChargePos = float4::Zero;

	float AccTime = 0.0f;
	float RevTime = 0.0f;
	float ChargeTime = 0.0f;
	float HitActionTime = 0.0f;
	
	int FireCount = 3;
	int CreateCount = 1;
	int RandCreate = 1;
	int Rand = 0;

	bool HitAction = false;
	bool IsCharge = false;
	bool IsBackUp = false;

	void RenderSet();
	void CollisionSet();
	void CollisionCheck();
	void Fire();
	void Fire_Red();
	void CreateExplosion();
	void CreatePoof();
	void Charge();
	int RandomNumberGeneration();

	Boss_TankState StateValue = Boss_TankState::IDLE;
	void ChangeState(Boss_TankState _State);
	void UpdateState(float _Time);

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void IdleRevStart();
	void IdleRevUpdate(float _DeltaTime);
	void IdleRevEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void ChargeStart();
	void ChargeUpdate(float _DeltaTime);
	void ChargeEnd();

	void BackUpStart();
	void BackUpUpdate(float _DeltaTime);
	void BackUpEnd();

	void FireStart();
	void FireUpdate(float _DeltaTime);
	void FireEnd();

	void HitStart();
	void HitUpdate(float _DeltaTime);
	void HitEnd();

};

