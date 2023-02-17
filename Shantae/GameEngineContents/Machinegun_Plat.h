#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class Soldier_Aim;

// Ό³Έν :
class Machinegun_Plat : public GameEngineActor
{
public:
	// constrcuter destructer
	Machinegun_Plat();
	~Machinegun_Plat();

	// delete Function
	Machinegun_Plat(const Machinegun_Plat& _Other) = delete;
	Machinegun_Plat(Machinegun_Plat&& _Other) noexcept = delete;
	Machinegun_Plat& operator=(const Machinegun_Plat& _Other) = delete;
	Machinegun_Plat& operator=(Machinegun_Plat&& _Other) noexcept = delete;

	void IsMisillieDeath(bool _Death)
	{
		MisillieDeath = _Death;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* MisillieCollision = nullptr;
	Soldier_Aim* NewAim = nullptr;

	int MisillieCount = 1;

	bool HitAction = false;
	bool IsCreate = false;
	bool IsDeath = false;
	bool MisillieDeath = false;

	void CollisionCheck();
	void MisillieCreate();
	void AimCreate();
	void Kill();
	void BreakGround();

	void RenderSet();
	void CollisionSet();

};

