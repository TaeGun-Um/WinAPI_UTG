#pragma once

#include <GameEngineCore/GameEngineActor.h>

class GameEngineImage;

enum class Soldier_SpiderState
{
	IDLE,
	MOVE,
	ATTACK,
	HIT,
};

// Ό³Έν : Player Chracter
class Soldier_Spider : public GameEngineActor
{
public:
	// constrcuter destructer
	Soldier_Spider();
	~Soldier_Spider();

	// delete Function
	Soldier_Spider(const Soldier_Spider& _Other) = delete;
	Soldier_Spider(Soldier_Spider&& _Other) noexcept = delete;
	Soldier_Spider& operator=(const Soldier_Spider& _Other) = delete;
	Soldier_Spider& operator=(Soldier_Spider&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

	void SetDir(const std::string_view& _Dir)
	{
		DirString = _Dir;
	}

	void SetAccTime(float _Timer)
	{
		AccTime = _Timer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* AttackCollision = nullptr;
	GameEngineCollision* SensorCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	float MoveSpeed = 0.0f;
	float AccTime = 0.0f;
	float AttackDelay = 0.0f;
	float HitTime = 0.0f;
	float BlinkTime = 0.0f;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;
	float4 ForwardPosR = float4::Zero;
	float4 ForwardPosL = float4::Zero;

	bool CollisionGround = false;
	bool IsGravity = true;
	bool MoveDirect = false;
	bool HitAction = false;
	bool IsAttack = false;
	bool Blinker = false;

	int ChangeCount = 1;
	int BlinkCount = 1;

	std::string DirString = "_R";
	Soldier_SpiderState StateValue = Soldier_SpiderState::MOVE;

	std::string DirCheck(const std::string_view& _AnimationName);
	void MoveCalculation(float _DeltaTime);
	void CollisionCheck();
	void Explosion();
	void Kill();
	void AlphaBlinker(float _DeltaTime);

	void RenderSet();
	void CollisionSet();

	void ChangeState(Soldier_SpiderState _State);
	void UpdateState(float _Time);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	void AttackStart();
	void AttackUpdate(float _Time);
	void AttackEnd();

	void HitStart();
	void HitUpdate(float _Time);
	void HitEnd();

};

