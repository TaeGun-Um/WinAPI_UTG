#pragma once

#include <GameEngineCore/GameEngineActor.h>

class GameEngineImage;

// Ό³Έν : Player Chracter
class Boss_Boom : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_Boom();
	~Boss_Boom();

	// delete Function
	Boss_Boom(const Boss_Boom& _Other) = delete;
	Boss_Boom(Boss_Boom&& _Other) noexcept = delete;
	Boss_Boom& operator=(const Boss_Boom& _Other) = delete;
	Boss_Boom& operator=(Boss_Boom&& _Other) noexcept = delete;

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
	GameEngineImage* ColMap = nullptr;

	float MoveSpeed = 100.0f;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;
	float4 OwnerPos = float4::Zero;

	void MoveCalculation(float _DeltaTime);
	void CollisionCheck();
	void Bounce();
	void Kill();
	void DirectCheckForKill();
	void Explosion();

};

