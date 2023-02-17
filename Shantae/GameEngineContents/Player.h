#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class GameEngineImage;

enum class PlayerState
{
	IDLE,
	REST,
	MOVE,
	MOVESTOP,
	JUMP,
	JUMPFALL,
	FALL,
	ATT,
	CROUCHATT,
	AIRATT,
	CROUCH,
	LAND,
	HIT,
	JUMPHIT,
	JUMPHIT2,
	CROUCHHIT,
};

// ���� : Player Chracter
class Player : public GameEngineActor
{
public:
	static Player* MainPlayer;

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	// ī�޶� �׼ǿ�
	bool GetShantaeMove()
	{
		return ShantaeMove;
	}
	bool GetCameraMove()
	{
		return CameraMove;
	}
	void ShantaeMoveSwitch()
	{
		ShantaeMove = !ShantaeMove;
	}
	void CameraMoveSwitch()
	{
		CameraMove = !CameraMove;
	}
	void CameraMoveFalse()
	{
		CameraMove = false;
	}
	void CameraMoveTrue()
	{
		CameraMove = true;
	}

	// ���ǵ� ����
	void SetMoveSpeed(float _Speed)
	{
		MoveSpeed = _Speed;
	}
	void SetCrouchSpeed(float _Speed)
	{
		CrouchSpeed = _Speed;
	}

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

	std::string& GetDir()
	{
		return DirString;
	}

	int GetPlayerHP()
	{
		return HP;
	}

	void SetPlayerHP(int _HP)
	{
		HP = _HP;
	}

	void PlusPlayerHP(int _PlusHP)
	{
		HP += _PlusHP;
	}
	
	int GetPlayerMaxHP()
	{
		return MaxHP;
	}

	void SetPlayerMaxHP(int _MaxHP)
	{
		MaxHP = _MaxHP;
	}

	void PlusPlayerMaxHP(int _PlusMaxHP)
	{
		MaxHP += _PlusMaxHP;
	}

	int GetPlayerGem()
	{
		return PlayerGem;
	}

	void SetPlayerGem(int _Gem)
	{
		PlayerGem = _Gem;
	}

	void PlusPlayerGem(int _PlusGem)
	{
		PlayerGem += _PlusGem;
	}

	bool FreeMoveState(float _DeltaTime);
	void PositionText();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineImage* ColMap = nullptr;

	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* AttackCollision = nullptr;
	GameEngineCollision* StandingCollision = nullptr;

	float4 MoveDir = float4::Zero;  // ���� �̵� ��ġ(������)
	float4 NextPos = float4::Zero;
	float4 ForwardPosR_Low = float4::Zero;
	float4 ForwardPosL_Low = float4::Zero;
	float4 ForwardPosR_High = float4::Zero;
	float4 ForwardPosL_High = float4::Zero;
	float4 CrouchUpPos_R = float4::Zero;
	float4 CrouchUpPos_L = float4::Zero;
	float4 UpPos = float4::Zero;
	float4 JumpLand = float4::Zero;

	float MoveSpeed = 600.0f;
	float CrouchSpeed = 200.0f;
	float GravitySpeed = 3500.0f;
	float OverlapTime = 0.0f;
	float MoveTime = 0.0f;
	float JumpTime = 0.0f;
	float FallTime = 0.0f;
	float JumpPos = 0.0f;
	float IdleTime = 0.0f;
	float HitTime = 0.0f;

	int Pass = 1;
	int MaxHP = 8;
	int HP = 8;
	int PlayerGem = 0;

	bool ShantaeMove = true;
	bool CameraMove  = true;
	bool IsGravity = true;
	bool IsGravityPlus = false;
	bool IsCrouch = false;
	bool CrouchMaintain = false;
	bool IsJump = false;
	bool Highest = false;
	bool Fall = true;
	bool DownJump = false;
	bool AirAttack = false;
	bool PosText = false;
	bool IsDeath = false;
	bool HitAction = false;
	bool HitTimeCheck = false;
	bool IsJumpHit = false;

	bool CollisionGround = false;

	bool AttackDir = true;
	bool IsAttackStart = false;
	bool IsAirAttack = false;
	bool IsCrouchAttack = false;
	bool IsAttack = false;

	float AccTime = 0.0f;
	int StartFrame = 0;             // cut�� ���� �ε��� ��ȣ

	// FSM == �Ѱ��� ���¿��� �Ѱ��� �ϸ� �Ѵ�.
	std::string DirString = "_R";
	PlayerState StateValue = PlayerState::IDLE;

	// bool GravityPlus();

	std::string DirCheck(const std::string_view& _AnimationName);
	void CollisionCheck(float _DeltaTime);
	void MoveCalculation(float _DeltaTime);
	void Shoot();
	void Kill();
	void WallCheck(float _Speed);

	void RenderSet();
	void CollisionSet();

	// State
	void ChangeState(PlayerState _State);
	void UpdateState(float _Time);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void IdleRestStart();
	void IdleRestUpdate(float _Time);
	void IdleRestEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	void JumpStart();
	void JumpUpdate(float _Time);
	void JumpEnd();

	void JumpFallStart();
	void JumpFallUpdate(float _Time);
	void JumpFallEnd();

	void FallStart();
	void FallUpdate(float _Time);
	void FallEnd();

	void AttackStart();
	void AttackUpdate(float _Time);
	void AttackEnd();

	void CrouchAttackStart();
	void CrouchAttackUpdate(float _Time);
	void CrouchAttackEnd();

	void AirAttackStart();
	void AirAttackUpdate(float _Time);
	void AirAttackEnd();

	void CrouchingStart();
	void CrouchingUpdate(float _Time);
	void CrouchingEnd();

	void MoveStopStart();
	void MoveStopUpdate(float _Time);
	void MoveStopEnd();

	void LandingStart();
	void LandingUpdate(float _Time);
	void LandingEnd();

	void HitStart();
	void HitUpdate(float _Time);
	void HitEnd();

	void JumpHitStart();
	void JumpHitUpdate(float _Time);
	void JumpHitEnd();

	void JumpHitStart2();
	void JumpHitUpdate2(float _Time);
	void JumpHitEnd2();

	void CrouchHitStart();
	void CrouchHitUpdate(float _Time);
	void CrouchHitEnd();

};
