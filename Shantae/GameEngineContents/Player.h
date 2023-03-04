#pragma once

#include <string_view>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/NumberRenderObject.h>
#include <GameEngineCore/GameEngineCollision.h>

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
	PORTALIN,
	PORTALING,
	PORTALOUT,
};

enum class NPCDialogType
{
	Sky,
	Bathwoman,
	Merchant,
	Squidsmith,
	Town_Guard,
	Town_Guard_Pass,
};

class PikeBallEffect;
class BubbleEffect;

// 설명 : Player Chracter
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

	// 카메라 액션용
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

	// 스피드 조절
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

	void SetDir(std::string _Dir)
	{
		DirString = _Dir;
	}

	void SetAnimationStart(bool _Is)
	{
		IsAnimationStart = _Is;
	}

	void SetRoomAnimationStart(bool _Is)
	{
		IsRoomAnimationStart = _Is;
	}

	void SetStartAnimationStart(bool _Is)
	{
		IsStartAnimationStart = _Is;
	}
	
	PlayerState GetShantaeState()
	{
		return StateValue;
	}

	GameEngineRender* GetShataeAnimationRender()
	{
		return AnimationRender;
	}

	void IsHouseSet(bool _Is)
	{
		IsHouse = _Is;
	}

	void SetPortalEnd(bool _Is)
	{
		PortalEnd = _Is;
	}

	void SetCameraShakinghard(float _SetShakingTime, float _SetShakingValue);
	void SetCameraShaking(float _SetShakingTime, float _SetShakingValu);
	bool FreeMoveState(float _DeltaTime);
	void PositionText();
	void ChangeState(PlayerState _State);
	bool LevelChangeAnimation(float _DeltaTime);
	bool RoomChangeAnimation(float _DeltaTime);
	void LevelStartAnimation(float _DeltaTime);

	GameEngineSoundPlayer BGMPlayer;
	GameEngineSoundPlayer CrouchMovePlayer;

	// Status
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

	int GetPlayerDamage()
	{
		return PlayerDamage;
	}

	void SetPlayerDamage(int _Value)
	{
		PlayerDamage += _Value;
	}

	int GetNewMaxHP()
	{
		return NewMaxHP;
	}

	void PlusNewMaxHP(int _Value)
	{
		NewMaxHP = MaxHP + _Value;
	}

	void SetNewMaxHP(int _NewMaxHP)
	{
		NewMaxHP = _NewMaxHP;
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

	int GetPlayerMonsterMilk()
	{
		return MonsterMilk;
	}

	void PlusPlayerMonsterMilk(int _MonsterMilk)
	{
		MonsterMilk += _MonsterMilk;
	}

	void SetPlayerMonsterMilk(int _MonsterMilk)
	{
		MonsterMilk = _MonsterMilk;
	}

	int GetPlayerMeat()
	{
		return Meat;
	}

	void PlusPlayerMeat(int _Meat)
	{
		Meat += _Meat;
	}

	void SetPlayerMeat(int _Meat)
	{
		Meat = _Meat;
	}

	int GetPlayerBubble()
	{
		return Bubble;
	}

	void PlusPlayerBubble(int _Bubble)
	{
		Bubble += _Bubble;
	}

	void SetPlayerBubble(int _Bubble)
	{
		Bubble = _Bubble;
	}

	int GetPlayerPikeBall()
	{
		return PikeBall;
	}

	void PlusPlayerPikeBall(int _PikeBall)
	{
		PikeBall += _PikeBall;
	}

	void SetPlayerPikeBall(int _PikeBall)
	{
		PikeBall = _PikeBall;
	}

	int GetPlayerOctopus()
	{
		return Octopus;
	}

	void PlusPlayerOctopus(int _Octopus)
	{
		Octopus += _Octopus;
	}

	void MinusPlayerOctopus(int _Octopus)
	{
		Octopus -= _Octopus;
	}

	void SetPlayerOctopus(int _Octopus)
	{
		Octopus = _Octopus;
	}

	int GetPlayerIDCard()
	{
		return IDCard;
	}

	void SetPlayerIDCard(int _IDCard)
	{
		IDCard = _IDCard;
	}

	bool GetItemEquip()
	{
		return IsItemEquip;
	}

	void SetItemEquip(bool _Is)
	{
		IsItemEquip = _Is;
	}

	void SetItemUse(std::string _Name)
	{
		IsItemUse = true;
		ItemName = _Name;
		InventorySoundCount = 1;
	}

	std::string GetUseItemName()
	{
		return ItemName;
	}

	bool GetTextActivate()
	{
		return TextActivate;
	}

	void ConversationOff()
	{
		InConversation = false;
	}

	void BodyCollisionOn()
	{
		BodyCollision->On();
	}

	void NPCType(NPCDialogType _Value)
	{
		DialogValue = _Value;
	}

	bool GetSkyScriptEnd()
	{
		return SkyScriptEnd;
	}

	void SetSkyScriptEnd()
	{
		SkyScriptEnd = true;
	}

	bool GetTownGuardScriptEnd()
	{
		return TownGuardScriptEnd;
	}

	void SetTownGuardScriptEnd()
	{
		TownGuardScriptEnd = true;
	}

	bool GetSquidsmithScriptEnd()
	{
		return SquidsmithScriptEnd;
	}

	void SetSquidsmithScriptEnd()
	{
		SquidsmithScriptEnd = true;
	}

	bool GetScuttlePass()
	{
		return ScuttlePass;
	}

	void SetScuttlePass()
	{
		ScuttlePass = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineLevel* CurrentLevel = nullptr;

	// Status
	int IDCard = 0;
	int MaxHP = 8;
	int NewMaxHP = 0;
	int HP = 8;
	int PlayerDamage = 5;
	int PlayerGem = 0;

	int MonsterMilk = 0;
	int Meat = 0;
	int Bubble = 0;
	int PikeBall = 0;
	int Octopus = 0;
	int Pass = 0;

	bool IsItemEquip = false;

	std::string DirCheck(const std::string_view& _AnimationName);
	void MoveCalculation(float _DeltaTime);
	void WallCheck(float _Speed);
	void CollisionCheck(float _DeltaTime);
	void WalkSoundSet(float _DeltaTime);
	void CameraShake(float _DeltaTime);
	void CameraShakehard(float _DeltaTime);
	void AlphaBlinker(float _DeltaTime);
	void CreateDummy();
	void CreateImpact();
	void Shoot();
	void Kill();
	void RenderSet();
	void CollisionSet();
	void ItemUse(float _DeltaTiem);
	void UseMonsterMilk(float _DeltaTiem);
	void UseMeat();
	void UseBubble(float _DeltaTiem);
	void UsePikeBall(float _DeltaTiem);

	float MonsterMilkTime = 0.0f;
	float BubbleTime = 0.0f;
	float PikeBallTime = 0.0f;

	int InventorySoundCount = 1;
	int MonsterMilkSet = 1;
	int BubbleSet = 1;
	int PikeBallSet = 1;

	PikeBallEffect* Pik = nullptr;
	BubbleEffect* Bub = nullptr;

	std::string ItemName = "Meat";

	bool TextActivate = false;
	bool InConversation = false;
	bool SkyScriptEnd = false;
	bool TownGuardScriptEnd = false;
	bool SquidsmithScriptEnd = false;
	bool ScuttlePass = false;

	NPCDialogType DialogValue = NPCDialogType::Town_Guard;

	bool IsItemUse = false;
	bool MonsterMilkEnd = false;
	bool PikeBallEnd = false;
	bool BubbleEnd = false;
	bool MeatEnd = false;

	GameEngineRender* AnimationRender = nullptr;
	GameEngineImage* ColMap = nullptr;

	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* AttackCollision = nullptr;
	GameEngineCollision* StandingCollision = nullptr;

	float4 MoveDir = float4::Zero;  // 최종 이동 위치(벡터합)
	float4 NextPos = float4::Zero;
	float4 ForwardPosR_Low = float4::Zero;
	float4 ForwardPosL_Low = float4::Zero;
	float4 ForwardPosR_High = float4::Zero;
	float4 ForwardPosL_High = float4::Zero;
	float4 CrouchUpPos_R = float4::Zero;
	float4 CrouchUpPos_L = float4::Zero;
	float4 UpPos = float4::Zero;
	float4 JumpLand = float4::Zero;
	float4 ImpactPos = float4::Zero;
	
	float MoveSpeed = 600.0f;
	float CrouchSpeed = 200.0f;
	float GravitySpeed = 3500.0f;
	float SetShakingValue = 0.0f;
	float SetShakingValuehard = 0.0f;

	float OverlapTime = 0.0f;
	float MoveTime = 0.0f;
	float JumpTime = 0.0f;
	float FallTime = 0.0f;
	float JumpPos = 0.0f;
	float IdleTime = 0.0f;
	float HitTime = 0.0f;
	float BlinkTime = 0.0f;

	float AnimationTime = 0.0f;
	float MoveSoundTime = 0.0f;
	float ShakingTime = 0.0f;
	float SetShakingTime = 0.0f;
	float CrouchMoveSoundTime = 0.0f;
	float ImpactRe = 0.0f;

	int ShakingCount = 0;
	int HardShakingCount = 0;
	int MoveSoundCount = 2;
	int CrouchMoveSoundCount = 1;
	int UpCol = 1;
	int ImpactCreate = 1;

	bool FreeMove = false;
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
	bool Blinker = false;
	bool CameraShaking = false;
	bool CameraShakinghard = false;
	bool CrouchHit = false;

	bool CollisionGround = false;
	bool InvenOnOff = false;

	bool AttackDir = true;
	bool IsAttackStart = false;
	bool IsAirAttack = false;
	bool IsCrouchAttack = false;
	bool IsAttack = false;
	bool IsAnimationStart = false;
	bool IsStartAnimationStart = false;
	bool IsRoomAnimationStart = false;
	bool IsHouse = false;
	bool PortalEnd = false;

	float AccTime = 0.0f;
	int StartFrame = 0;             // cut을 위한 인덱스 번호

	// FSM == 한가지 상태에선 한가지 일만 한다.
	std::string DirString = "_R";
	PlayerState StateValue = PlayerState::IDLE;

	// State
	
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

	void PortalInStart();
	void PortalInUpdate(float _Time);
	void PortalInEnd();

	void PortalingStart();
	void PortalingUpdate(float _Time);
	void PortalingEnd();

	void PortalOutStart();
	void PortalOutUpdate(float _Time);
	void PortalOutEnd();

};

