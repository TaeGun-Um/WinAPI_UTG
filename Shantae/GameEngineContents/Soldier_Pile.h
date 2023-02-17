#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

// Ό³Έν :
class Soldier_Pile : public GameEngineActor
{
public:
	// constrcuter destructer
	Soldier_Pile();
	~Soldier_Pile();

	// delete Function
	Soldier_Pile(const Soldier_Pile& _Other) = delete;
	Soldier_Pile(Soldier_Pile&& _Other) noexcept = delete;
	Soldier_Pile& operator=(const Soldier_Pile& _Other) = delete;
	Soldier_Pile& operator=(Soldier_Pile&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

