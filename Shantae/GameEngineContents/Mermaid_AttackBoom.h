#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Mermaid_AttackBoom : public GameEngineActor
{
public:
	// constrcuter destructer
	Mermaid_AttackBoom();
	~Mermaid_AttackBoom();

	// delete Function
	Mermaid_AttackBoom(const Mermaid_AttackBoom& _Other) = delete;
	Mermaid_AttackBoom(Mermaid_AttackBoom&& _Other) noexcept = delete;
	Mermaid_AttackBoom& operator=(const Mermaid_AttackBoom& _Other) = delete;
	Mermaid_AttackBoom& operator=(Mermaid_AttackBoom&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

};

