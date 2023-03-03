#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class GameEngineImage;

enum class Soldier_BombermanState
{
	CROUCH,
	LOB,
	HIT,
};

// Ό³Έν : Player Chracter
class Soldier_Bomberman : public GameEngineActor
{
public:
	// constrcuter destructer
	Soldier_Bomberman();
	~Soldier_Bomberman();

	// delete Function
	Soldier_Bomberman(const Soldier_Bomberman& _Other) = delete;
	Soldier_Bomberman(Soldier_Bomberman&& _Other) noexcept = delete;
	Soldier_Bomberman& operator=(const Soldier_Bomberman& _Other) = delete;
	Soldier_Bomberman& operator=(Soldier_Bomberman&& _Other) noexcept = delete;

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

	GameEngineSoundPlayer BGMPlayer;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;

	float HitTime = 0.0f;
	float LobStatTime = 0.0f;
	float BlinkTime = 0.0f;

	// true = left, false = right
	bool MoveDirect = true;
	bool IsGravity = true;
	bool IsTurn = false;
	bool HitAction = false;
	bool IsDeath = false;
	bool trace = true;
	bool Blinker = false;

	int BoomCount = 1;

	std::string DirString = "_L";
	std::string HitDir = "_L";
	Soldier_BombermanState StateValue = Soldier_BombermanState::CROUCH;	

	std::string DirCheck(const std::string_view& _AnimationName);
	void CharacterDirectSetting(float _DeltaTime);
	void MoveCalculation(float _DeltaTime);
	void CollisionCheck();
	void Explosion();
	void Throw();
	void Kill();
	void AlphaBlinker(float _DeltaTime);
	void CreateItem();
	void CreateText();

	void RenderSet();
	void CollisionSet();

	void ChangeState(Soldier_BombermanState _State);
	void UpdateState(float _Time);

	void CrouchStart();
	void CrouchUpdate(float _Time);
	void CrouchEnd();

	void LobStart();
	void LobUpdate(float _Time);
	void LobEnd();

	void HitStart();
	void HitUpdate(float _Time);
	void HitEnd();

};

