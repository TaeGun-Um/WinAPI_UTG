#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineImage;

enum class MermaidState
{
	IDLE,
	LURE,
	READY,
	HOLD,
	DIVE,
	EMERGE,
	SHOOT,
	HIT,
	DIE
};

// Ό³Έν : Player Chracter
class Mermaid : public GameEngineActor
{
public:
	// constrcuter destructer
	Mermaid();
	~Mermaid();

	// delete Function
	Mermaid(const Mermaid& _Other) = delete;
	Mermaid(Mermaid&& _Other) noexcept = delete;
	Mermaid& operator=(const Mermaid& _Other) = delete;
	Mermaid& operator=(Mermaid&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

	void SetDirect(bool _Is)
	{
		MoveDirect = _Is;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void MoveCalculation(float _DeltaTime);
	void CollisionCheck(float _DeltaTime);
	void Shoot();
	void Kill();
	void AlphaBlinker(float _DeltaTime);

	void RenderSet();
	void CollisionSet();

	GameEngineSoundPlayer BGMPlayer;

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* SensorCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;

	float HitTime = 0.0f;
	float ShootStartTime = 0.0f;
	float HoldTime = 0.0f;
	float ShootTime = 0.0f;
	float BlinkTime = 0.0f;
	float LureTime = 0.0f;
	float DiveTime = 0.0f;

	// true = left, false = right
	bool MoveDirect = true;
	bool IsGravity = true;
	bool IsTurn = false;
	bool HitAction = false;
	bool IsDeath = false;
	bool Blinker = false;
	bool IsAttack = false;

	int ShootCount = 1;
	int HP = 15;
	int HitSet = 1;

	std::string DirString = "_L";
	std::string HitDir = "_L";
	MermaidState StateValue = MermaidState::IDLE;

	std::string DirCheck(const std::string_view& _AnimationName);

	void ChangeState(MermaidState _State);
	void UpdateState(float _Time);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void LureStart();
	void LureUpdate(float _Time);
	void LureEnd();

	void ReadyStart();
	void ReadyUpdate(float _Time);
	void ReadyEnd();

	void HoldStart();
	void HoldUpdate(float _Time);
	void HoldEnd();

	void DiveStart();
	void DiveUpdate(float _Time);
	void DiveEnd();

	void EmergeStart();
	void EmergeUpdate(float _Time);
	void EmergeEnd();

	void ShootStart();
	void ShootUpdate(float _Time);
	void ShootEnd();

	void HitStart();
	void HitUpdate(float _Time);
	void HitEnd();

	void DieStart();
	void DieUpdate(float _Time);
	void DieEnd();

};

