#pragma once

#include <GameEngineCore/GameEngineActor.h>

class GameEngineImage;

enum class ScarecrowState
{
	MOVE,
	HIT,
};

// Ό³Έν : Player Chracter
class Scarecrow : public GameEngineActor
{
public:
	// constrcuter destructer
	Scarecrow();
	~Scarecrow();

	// delete Function
	Scarecrow(const Scarecrow& _Other) = delete;
	Scarecrow(Scarecrow&& _Other) noexcept = delete;
	Scarecrow& operator=(const Scarecrow& _Other) = delete;
	Scarecrow& operator=(Scarecrow&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;
	GameEngineRender* DamageText = nullptr;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;

	float4 TextPos = float4::Zero;

	bool Hitonoff = false;
	bool CreateT = false;

	float HitTime = 0.0f;

	void CollisionCheck(float _DeltaTime);
	void MoveCalculation(float _DeltaTime);
	void Kill();
	void CreateText();
};

