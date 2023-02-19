#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Public_Boom : public GameEngineActor
{
public:
	// constrcuter destructer
	Public_Boom();
	~Public_Boom();

	// delete Function
	Public_Boom(const Public_Boom& _Other) = delete;
	Public_Boom(Public_Boom&& _Other) noexcept = delete;
	Public_Boom& operator=(const Public_Boom& _Other) = delete;
	Public_Boom& operator=(Public_Boom&& _Other) noexcept = delete;

	void ExplosionPlus(float _Time);

	void SetExPlus(int _Value)
	{
		Plus = _Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	float ExPlusTime = 0.0f;
	int Plus = 0;
};

