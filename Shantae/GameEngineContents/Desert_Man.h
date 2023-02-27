#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Desert_Man : public GameEngineActor
{
public:
	// constrcuter destructer
	Desert_Man();
	~Desert_Man();

	// delete Function
	Desert_Man(const Desert_Man& _Other) = delete;
	Desert_Man(Desert_Man&& _Other) noexcept = delete;
	Desert_Man& operator=(const Desert_Man& _Other) = delete;
	Desert_Man& operator=(Desert_Man&& _Other) noexcept = delete;

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

