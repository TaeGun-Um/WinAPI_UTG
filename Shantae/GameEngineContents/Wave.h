#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Wave : public GameEngineActor
{
public:
	// constrcuter destructer
	Wave();
	~Wave();

	// delete Function
	Wave(const Wave& _Other) = delete;
	Wave(Wave&& _Other) noexcept = delete;
	Wave& operator=(const Wave& _Other) = delete;
	Wave& operator=(Wave&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

