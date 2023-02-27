#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Jug_Woman : public GameEngineActor
{
public:
	// constrcuter destructer
	Jug_Woman();
	~Jug_Woman();

	// delete Function
	Jug_Woman(const Jug_Woman& _Other) = delete;
	Jug_Woman(Jug_Woman&& _Other) noexcept = delete;
	Jug_Woman& operator=(const Jug_Woman& _Other) = delete;
	Jug_Woman& operator=(Jug_Woman&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Run();
	void Move();

	GameEngineRender* AnimationRender = nullptr;
	bool MoveDirect = true; // true = Left, false = Right

};

