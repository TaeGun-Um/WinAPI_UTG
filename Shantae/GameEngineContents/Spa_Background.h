#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Spa_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	Spa_Background();
	~Spa_Background();

	// delete Function
	Spa_Background(const Spa_Background& _Other) = delete;
	Spa_Background(Spa_Background&& _Other) noexcept = delete;
	Spa_Background& operator=(const Spa_Background& _Other) = delete;
	Spa_Background& operator=(Spa_Background&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

