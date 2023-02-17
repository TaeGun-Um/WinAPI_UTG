#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Spa_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Spa_Map();
	~Spa_Map();

	// delete Function
	Spa_Map(const Spa_Map& _Other) = delete;
	Spa_Map(Spa_Map&& _Other) noexcept = delete;
	Spa_Map& operator=(const Spa_Map& _Other) = delete;
	Spa_Map& operator=(Spa_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

