#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Scuttle_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Scuttle_Map();
	~Scuttle_Map();

	// delete Function
	Scuttle_Map(const Scuttle_Map& _Other) = delete;
	Scuttle_Map(Scuttle_Map&& _Other) noexcept = delete;
	Scuttle_Map& operator=(const Scuttle_Map& _Other) = delete;
	Scuttle_Map& operator=(Scuttle_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

