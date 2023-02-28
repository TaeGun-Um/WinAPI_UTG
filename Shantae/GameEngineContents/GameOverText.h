#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameOverText : public GameEngineActor
{
public:
	static bool IsEnd;

	// constrcuter destructer
	GameOverText();
	~GameOverText();

	// delete Function
	GameOverText(const GameOverText& _Other) = delete;
	GameOverText(GameOverText&& _Other) noexcept = delete;
	GameOverText& operator=(const GameOverText& _Other) = delete;
	GameOverText& operator=(GameOverText&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

	float AlphaTime = 0;
	float DelayTime = 0;
	int AlphaValue = 0;

	bool Doubling = false;
};

