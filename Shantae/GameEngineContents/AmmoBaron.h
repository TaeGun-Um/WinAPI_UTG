#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class GameEngineImage;

enum class AmmoBaronState
{
	MOVE,
	HIT,
};

// Ό³Έν : Player Chracter
class AmmoBaron : public GameEngineActor
{
public:
	// constrcuter destructer
	AmmoBaron();
	~AmmoBaron();

	// delete Function
	AmmoBaron(const AmmoBaron& _Other) = delete;
	AmmoBaron(AmmoBaron&& _Other) noexcept = delete;
	AmmoBaron& operator=(const AmmoBaron& _Other) = delete;
	AmmoBaron& operator=(AmmoBaron&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	NumberRenderObject TestNumber;

};

