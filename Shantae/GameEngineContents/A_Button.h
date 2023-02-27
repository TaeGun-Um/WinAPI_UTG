#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class A_Button : public GameEngineActor
{
public:
	// constrcuter destructer
	A_Button();
	~A_Button();

	// delete Function
	A_Button(const A_Button& _Other) = delete;
	A_Button(A_Button&& _Other) noexcept = delete;
	A_Button& operator=(const A_Button& _Other) = delete;
	A_Button& operator=(A_Button&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

