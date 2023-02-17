#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Spa_Sea : public GameEngineActor
{
public:
	// constrcuter destructer
	Spa_Sea();
	~Spa_Sea();

	// delete Function
	Spa_Sea(const Spa_Sea& _Other) = delete;
	Spa_Sea(Spa_Sea&& _Other) noexcept = delete;
	Spa_Sea& operator=(const Spa_Sea& _Other) = delete;
	Spa_Sea& operator=(Spa_Sea&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

