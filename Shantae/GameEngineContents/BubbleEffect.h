#pragma once

#include <GameEngineCore/GameEngineActor.h>

class Player;

// Ό³Έν : Player Chracter
class BubbleEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	BubbleEffect();
	~BubbleEffect();

	// delete Function
	BubbleEffect(const BubbleEffect& _Other) = delete;
	BubbleEffect(BubbleEffect&& _Other) noexcept = delete;
	BubbleEffect& operator=(const BubbleEffect& _Other) = delete;
	BubbleEffect& operator=(BubbleEffect&& _Other) noexcept = delete;

	void Kill();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

	float EndTime = 0.0f;

};

