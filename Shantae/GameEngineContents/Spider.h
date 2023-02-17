#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class GameEngineImage;

enum class SpiderState
{
	MOVE,
	HIT,
};

// Ό³Έν : Player Chracter
class Spider : public GameEngineActor
{
public:
	// constrcuter destructer
	Spider();
	~Spider();

	// delete Function
	Spider(const Spider& _Other) = delete;
	Spider(Spider&& _Other) noexcept = delete;
	Spider& operator=(const Spider& _Other) = delete;
	Spider& operator=(Spider&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	NumberRenderObject TestNumber;

};

