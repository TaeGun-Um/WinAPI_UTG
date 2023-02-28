#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Mermaid_Attack : public GameEngineActor
{
public:
	// constrcuter destructer
	Mermaid_Attack();
	~Mermaid_Attack();

	// delete Function
	Mermaid_Attack(const Mermaid_Attack& _Other) = delete;
	Mermaid_Attack(Mermaid_Attack&& _Other) noexcept = delete;
	Mermaid_Attack& operator=(const Mermaid_Attack& _Other) = delete;
	Mermaid_Attack& operator=(Mermaid_Attack&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DirectCheckForKill();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	float4 CurrentPos = float4::Zero;

};

