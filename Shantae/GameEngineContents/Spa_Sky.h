#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Spa_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	Spa_Sky();
	~Spa_Sky();

	// delete Function
	Spa_Sky(const Spa_Sky& _Other) = delete;
	Spa_Sky(Spa_Sky&& _Other) noexcept = delete;
	Spa_Sky& operator=(const Spa_Sky& _Other) = delete;
	Spa_Sky& operator=(Spa_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

