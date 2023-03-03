#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class GameEngineImage;

enum class Soldier_RedState
{
	MOVE,
	MOVESTOP,
	JUMP,
	JUMPWALL,
	AMBUSH,
	HIT,
};

// Ό³Έν : Player Chracter
class Soldier_Red : public GameEngineActor
{
public:
	// constrcuter destructer
	Soldier_Red();
	~Soldier_Red();

	// delete Function
	Soldier_Red(const Soldier_Red& _Other) = delete;
	Soldier_Red(Soldier_Red&& _Other) noexcept = delete;
	Soldier_Red& operator=(const Soldier_Red& _Other) = delete;
	Soldier_Red& operator=(Soldier_Red&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

	void MoveDirectSwitch()
	{
		MoveDirect = !MoveDirect;
	}

	void SetMoveSpeed()
	{
		MoveSpeed = 0;
	}

	void SetAmbushTrue()
	{
		IsAmbush = true;
	}

	void SetAmbush();

	GameEngineSoundPlayer BGMPlayer;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	int State = 1;
	int AmbushJump = 1;
	int HP = 10;

	float MoveSpeed = 500.0f;
	float HitTime = 0.0f;
	float AmbushTime = 0.0f;
	float BlinkTime = 0.0f;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;
	float4 ForwardPosR_Low = float4::Zero;
	float4 ForwardPosL_Low = float4::Zero;
	float4 ForwardPosR_High = float4::Zero;
	float4 ForwardPosL_High = float4::Zero;
	float4 JumpP = float4::Zero;

	// true = left, false = right
	bool MoveDirect = true;
	bool IsAmbush = false;
	bool IsGravity = true;
	bool IsGravityPlus = false;
	bool IsJump = false;
	bool IsJumpWall = false;
	bool IsTurn = false;
	bool HitAction = false;
	bool IsDeath = false;
	bool Blinker = false;

	std::string DirString = "_L";
	std::string HitDir = "_L";
	Soldier_RedState StateValue = Soldier_RedState::MOVE;

	std::string DirCheck(const std::string_view& _AnimationName);
	void MoveCalculation(float _DeltaTime);
	void CollisionCheck();
	void Explosion();
	void Kill();
	void AlphaBlinker(float _DeltaTime);
	void CreateItem();
	void CreateText();

	void RenderSet();
	void CollisionSet();

	void ChangeState(Soldier_RedState _State);
	void UpdateState(float _Time);

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	void MoveStopStart();
	void MoveStopUpdate(float _Time);
	void MoveStopEnd();

	void JumpStart();
	void JumpUpdate(float _Time);
	void JumpEnd();

	void JumpWallStart();
	void JumpWallUpdate(float _Time);
	void JumpWallEnd();

	void AmbushStart();
	void AmbushUpdate(float _Time);
	void AmbushEnd();

	void HitStart();
	void HitUpdate(float _Time);
	void HitEnd();

};

