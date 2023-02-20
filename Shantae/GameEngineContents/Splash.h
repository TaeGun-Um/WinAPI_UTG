#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Splash : public GameEngineActor
{
public:
	// constrcuter destructer
	Splash();
	~Splash();

	// delete Function
	Splash(const Splash& _Other) = delete;
	Splash(Splash&& _Other) noexcept = delete;
	Splash& operator=(const Splash& _Other) = delete;
	Splash& operator=(Splash&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

