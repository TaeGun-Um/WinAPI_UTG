#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineImage;

enum class CacklebatState
{
	IDLE,
	HIT,
};

// Ό³Έν : Player Chracter
class Cacklebat : public GameEngineActor
{
public:
	// constrcuter destructer
	Cacklebat();
	~Cacklebat();

	// delete Function
	Cacklebat(const Cacklebat& _Other) = delete;
	Cacklebat(Cacklebat&& _Other) noexcept = delete;
	Cacklebat& operator=(const Cacklebat& _Other) = delete;
	Cacklebat& operator=(Cacklebat&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CharacterDirectSetting(float _DeltaTime);
	void MoveCalculation(float _DeltaTime);
	void CollisionCheck(float _DeltaTime);
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
	float HitTime2 = 0.0f;
	float ShootStartTime = 0.0f;
	float ShootTime = 0.0f;
	float BlinkTime = 0.0f;

	bool MoveDirect = true;
	bool IsGravity = true;
	bool IsTurn = false;
	bool HitAction = false;
	bool IsDeath = false;
	bool trace = true;
	bool Hitonoff = true;
	bool Blinker = false;
	bool IsAttack = false;

	int HP = 0;

	std::string DirString = "_L";
	std::string HitDir = "_L";
	CacklebatState StateValue = CacklebatState::IDLE;

	std::string DirCheck(const std::string_view& _AnimationName);

	void ChangeState(CacklebatState _State);
	void UpdateState(float _Time);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

};

