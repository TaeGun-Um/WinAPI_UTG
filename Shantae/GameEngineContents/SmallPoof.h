#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class SmallPoof : public GameEngineActor
{
public:
	// constrcuter destructer
	SmallPoof();
	~SmallPoof();

	// delete Function
	SmallPoof(const SmallPoof& _Other) = delete;
	SmallPoof(SmallPoof&& _Other) noexcept = delete;
	SmallPoof& operator=(const SmallPoof& _Other) = delete;
	SmallPoof& operator=(SmallPoof&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

};

