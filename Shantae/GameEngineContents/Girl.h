#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Girl : public GameEngineActor
{
public:
	// constrcuter destructer
	Girl();
	~Girl();

	// delete Function
	Girl(const Girl& _Other) = delete;
	Girl(Girl&& _Other) noexcept = delete;
	Girl& operator=(const Girl& _Other) = delete;
	Girl& operator=(Girl&& _Other) noexcept = delete;

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

