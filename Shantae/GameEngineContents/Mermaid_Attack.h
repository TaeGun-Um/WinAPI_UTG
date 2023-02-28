#pragma once

#include <GameEngineCore/GameEngineActor.h>

class GameEngineImage;

// Ό³Έν : Player Chracter
class Mermaid_Attack : public GameEngineActor
{
public:
	// constrcuter destructer
	Mermaid_Attack();
	~Mermaid_Attack();

	// delete Function
	Mermaid_Attack(const Mermaid_Attack& _Other) = delete;
	Mermaid_Attack(Mermaid_Attack&& _Other) noexcept = delete;
	Mermaid_Attack& operator=(const Mermaid_Attack& _Other) = delete;
	Mermaid_Attack& operator=(Mermaid_Attack&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

	void SetOwnerPos(const float4& _Pos)
	{
		OwnerPos = _Pos;
	}

	void SetDir(const std::string_view& _Dir)
	{
		DirString = _Dir;
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

	float4 OwnerPos = float4::Zero;
	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;
	float4 ForwardPosR_Low = float4::Zero;
	float4 ForwardPosL_Low = float4::Zero;
	float4 ForwardPosR_High = float4::Zero;
	float4 ForwardPosL_High = float4::Zero;

	bool IsGravity = true;
	bool IsStart = true;
	bool IsDeath = false;

	// true = left, false = right
	bool MoveDirect = true;
	bool HitAction = true;

	void MoveCalculation(float _DeltaTime);
	void CollisionCheck();
	void KillBullet();
	void Explosion();

	std::string DirCheck(const std::string_view& _AnimationName);
	std::string DirString = "_L";

};

