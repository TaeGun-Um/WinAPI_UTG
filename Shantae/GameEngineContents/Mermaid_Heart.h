#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Mermaid_Heart : public GameEngineActor
{
public:
	// constrcuter destructer
	Mermaid_Heart();
	~Mermaid_Heart();

	// delete Function
	Mermaid_Heart(const Mermaid_Heart& _Other) = delete;
	Mermaid_Heart(Mermaid_Heart&& _Other) noexcept = delete;
	Mermaid_Heart& operator=(const Mermaid_Heart& _Other) = delete;
	Mermaid_Heart& operator=(Mermaid_Heart&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

};

