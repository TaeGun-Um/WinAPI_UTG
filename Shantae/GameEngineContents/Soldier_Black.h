#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class GameEngineImage;

enum class Soldier_BlackState
{
	IDLE,
	SHOOT,
	RELOAD,
	HIT,
};

// Ό³Έν : Player Chracter
class Soldier_Black : public GameEngineActor
{
public:
	// constrcuter destructer
	Soldier_Black();
	~Soldier_Black();

	// delete Function
	Soldier_Black(const Soldier_Black& _Other) = delete;
	Soldier_Black(Soldier_Black&& _Other) noexcept = delete;
	Soldier_Black& operator=(const Soldier_Black& _Other) = delete;
	Soldier_Black& operator=(Soldier_Black&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

	void MoveDirectSwitch()
	{
		MoveDirect = !MoveDirect;
	}

	const std::string GetDir()
	{
		return DirString;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineSoundPlayer BGMPlayer;

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* SensorCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;

	float HitTime = 0.0f;
	float HitTime2 = 0.0f;
	float ShootStartTime = 0.0f;
	float ShootTime = 0.0f;
	float BlinkTime = 0.0f;

	// true = left, false = right
	bool MoveDirect = true;
	bool IsGravity = true;
	bool IsTurn = false;
	bool HitAction = false;
	bool IsDeath = false;
	bool trace = true;
	bool Hitonoff = true;
	bool Blinker = false;
	bool IsAttack = false;

	int ShootCount = 3;
	int HP = 15;
	int HitSet = 1;

	std::string DirString = "_L";
	std::string HitDir = "_L";
	Soldier_BlackState StateValue = Soldier_BlackState::IDLE;

	std::string DirCheck(const std::string_view& _AnimationName);
	void CharacterDirectSetting(float _DeltaTime);
	void MoveCalculation(float _DeltaTime);
	void CollisionCheck(float _DeltaTime);
	void Explosion();
	void Shoot();
	void Kill();
	void AlphaBlinker(float _DeltaTime);
	void CreateItem();

	void RenderSet();
	void CollisionSet();

	void ChangeState(Soldier_BlackState _State);
	void UpdateState(float _Time);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void ShootStart();
	void ShootUpdate(float _Time);
	void ShootEnd();

	void ReloadStart();
	void ReloadUpdate(float _Time);
	void ReloadEnd();

	void HitStart();
	void HitUpdate(float _Time);
	void HitEnd();

};

