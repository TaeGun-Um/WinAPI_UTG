#pragma once

#include <GameEngineCore/GameEngineActor.h>

class GameEngineImage;

// Ό³Έν : Player Chracter
class Boss_Boom_Red : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_Boom_Red();
	~Boss_Boom_Red();

	// delete Function
	Boss_Boom_Red(const Boss_Boom_Red& _Other) = delete;
	Boss_Boom_Red(Boss_Boom_Red&& _Other) noexcept = delete;
	Boss_Boom_Red& operator=(const Boss_Boom_Red& _Other) = delete;
	Boss_Boom_Red& operator=(Boss_Boom_Red&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

	void SetOwnerPos(const float4& _Pos)
	{
		OwnerPos = _Pos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* AttackCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	float MoveSpeed = 500.0f;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;
	float4 OwnerPos = float4::Zero;

	bool ChangeDir = false;

	void MoveCalculation(float _DeltaTime);
	void CollisionCheck();
	void Change(float _DeltaTime);
	void Bounce();
	void Kill();
	void DirectCheckForKill();
	void Explosion();

};

