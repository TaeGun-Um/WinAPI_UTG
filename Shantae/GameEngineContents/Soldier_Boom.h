#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class GameEngineImage;

// Ό³Έν : Player Chracter
class Soldier_Boom : public GameEngineActor
{
public:
	// constrcuter destructer
	Soldier_Boom();
	~Soldier_Boom();

	// delete Function
	Soldier_Boom(const Soldier_Boom& _Other) = delete;
	Soldier_Boom(Soldier_Boom&& _Other) noexcept = delete;
	Soldier_Boom& operator=(const Soldier_Boom& _Other) = delete;
	Soldier_Boom& operator=(Soldier_Boom&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

	void SetDir(const std::string_view& _Dir)
	{
		DirString = _Dir;
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

	float MoveSpeed = 100.0f;

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

	int BoomThrowSound = 1;

	void MoveCalculation(float _DeltaTime);
	void CollisionCheck();
	void Kill();
	void Explosion();

	std::string DirCheck(const std::string_view& _AnimationName);
	std::string DirString = "_L";
};

