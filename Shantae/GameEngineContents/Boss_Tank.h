#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class GameEngineImage;
class AmmoBaron;

enum class Boss_TankState
{
	IDLE,
	IDLEREV,
	PUSHOUT,
	CHARGE,
	BACKUP,
	FIRE,
	HIT,
	EMPTY,
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

	GameEngineSoundPlayer BGMPlayer;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void RenderSet();
	void CollisionSet();
	void CollisionCheck();

	void Fire();
	void Fire_Red();
	void CreateExplosion();
	void CreateAmmoBaron();
	void Explosions(float4 _Value);
	void RandomCreateExplosion(float _DeltaTime);
	void CreatePoof();
	int RandomNumberGeneration();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;
	GameEngineActor* Ammo = nullptr;
	AmmoBaron* Baron = nullptr;

	float4 BossPos = float4::Zero;
	float4 ChargePos = float4::Zero;
	float4 PushoutPos = float4::Zero;

	float AccTime = 0.0f;
	float RevTime = 0.0f;
	float ChargeTime = 0.0f;
	float PushoutTime = 0.0f;
	float ExplosionTime = 0.0f;
	float RandomExplosionTime = 0.0f;
	float PopCornSoundTime = 0.0f;
	
	int BaronCreate = 1;
	int BaronStart = 1;
	int FireCount = 3;
	int CreateCount = 1;
	int RandCreate = 1;
	int Rand = 0;
	int PopcornSound = 3;

	bool HitAction = false;
	bool IsCharge = false;
	bool IsBackUp = false;
	bool IsPopCornSound = false;

	Boss_TankState StateValue = Boss_TankState::IDLE;
	void ChangeState(Boss_TankState _State);
	void UpdateState(float _Time);

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void IdleRevStart();
	void IdleRevUpdate(float _DeltaTime);
	void IdleRevEnd();

	void PushoutStart();
	void PushoutUpdate(float _DeltaTime);
	void PushoutEnd();

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

	void EmptyStart();
	void EmptyUpdate(float _DeltaTime);
	void EmptyEnd();

};

