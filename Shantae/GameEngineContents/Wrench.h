#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Wrench : public GameEngineActor
{
public:
	// constrcuter destructer
	Wrench();
	~Wrench();

	// delete Function
	Wrench(const Wrench& _Other) = delete;
	Wrench(Wrench&& _Other) noexcept = delete;
	Wrench& operator=(const Wrench& _Other) = delete;
	Wrench& operator=(Wrench&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

