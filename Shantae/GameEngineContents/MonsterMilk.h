#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MonsterMilk : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterMilk();
	~MonsterMilk();

	// delete Function
	MonsterMilk(const MonsterMilk& _Other) = delete;
	MonsterMilk(MonsterMilk&& _Other) noexcept = delete;
	MonsterMilk& operator=(const MonsterMilk& _Other) = delete;
	MonsterMilk& operator=(MonsterMilk&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

