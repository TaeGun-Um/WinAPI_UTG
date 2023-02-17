#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class GameEngineImage;

enum class MermaidState
{
	MOVE,
	HIT,
};

// Ό³Έν : Player Chracter
class Mermaid : public GameEngineActor
{
public:
	// constrcuter destructer
	Mermaid();
	~Mermaid();

	// delete Function
	Mermaid(const Mermaid& _Other) = delete;
	Mermaid(Mermaid&& _Other) noexcept = delete;
	Mermaid& operator=(const Mermaid& _Other) = delete;
	Mermaid& operator=(Mermaid&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	NumberRenderObject TestNumber;

};

