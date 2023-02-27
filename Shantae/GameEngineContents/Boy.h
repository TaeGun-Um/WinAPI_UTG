#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Boy : public GameEngineActor
{
public:
	// constrcuter destructer
	Boy();
	~Boy();

	// delete Function
	Boy(const Boy& _Other) = delete;
	Boy(Boy&& _Other) noexcept = delete;
	Boy& operator=(const Boy& _Other) = delete;
	Boy& operator=(Boy&& _Other) noexcept = delete;

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

