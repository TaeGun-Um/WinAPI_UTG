#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class Machinegun_Plat;

// Ό³Έν : Player Chracter
class Misillie : public GameEngineActor
{
public:
	// constrcuter destructer
	Misillie();
	~Misillie();

	// delete Function
	Misillie(const Misillie& _Other) = delete;
	Misillie(Misillie&& _Other) noexcept = delete;
	Misillie& operator=(const Misillie& _Other) = delete;
	Misillie& operator=(Misillie&& _Other) noexcept = delete;

	void SetOwnerPlat(Machinegun_Plat* _Machinegun_Plat)
	{
		OwnerPlat = _Machinegun_Plat;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	Machinegun_Plat* OwnerPlat = nullptr;

	float MoveSpeed = 250.0f;

	int Boomcount = 1;

	bool IsDeath = false;

	void MoveCalculation(float _DeltaTime);
	void CollisionCheck();
	void Kill();
	void Explosion();

};

