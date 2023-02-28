#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Bubble : public GameEngineActor
{
public:
	// constrcuter destructer
	Bubble();
	~Bubble();

	// delete Function
	Bubble(const Bubble& _Other) = delete;
	Bubble(Bubble&& _Other) noexcept = delete;
	Bubble& operator=(const Bubble& _Other) = delete;
	Bubble& operator=(Bubble&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

