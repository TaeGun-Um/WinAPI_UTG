#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Stylist : public GameEngineActor
{
public:
	// constrcuter destructer
	Stylist();
	~Stylist();

	// delete Function
	Stylist(const Stylist& _Other) = delete;
	Stylist(Stylist&& _Other) noexcept = delete;
	Stylist& operator=(const Stylist& _Other) = delete;
	Stylist& operator=(Stylist&& _Other) noexcept = delete;

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

