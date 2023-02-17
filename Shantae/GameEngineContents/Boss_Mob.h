#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class GameEngineImage;

enum class Boss_MobState
{
	MOVE,
	HIT,
};

// Ό³Έν : Player Chracter
class Boss_Mob : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_Mob();
	~Boss_Mob();

	// delete Function
	Boss_Mob(const Boss_Mob& _Other) = delete;
	Boss_Mob(Boss_Mob&& _Other) noexcept = delete;
	Boss_Mob& operator=(const Boss_Mob& _Other) = delete;
	Boss_Mob& operator=(Boss_Mob&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	NumberRenderObject TestNumber;

};

