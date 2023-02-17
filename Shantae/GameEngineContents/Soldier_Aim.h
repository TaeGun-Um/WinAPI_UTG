#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

// Ό³Έν :
class Soldier_Aim : public GameEngineActor
{
public:
	// constrcuter destructer
	Soldier_Aim();
	~Soldier_Aim();

	// delete Function
	Soldier_Aim(const Soldier_Aim& _Other) = delete;
	Soldier_Aim(Soldier_Aim&& _Other) noexcept = delete;
	Soldier_Aim& operator=(const Soldier_Aim& _Other) = delete;
	Soldier_Aim& operator=(Soldier_Aim&& _Other) noexcept = delete;

	void SetDeath(bool _IsDeath)
	{
		IsDeath = _IsDeath;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

	bool IsDeath = false;

};

