#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Move0 Map
class Move0_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Move0_Map();
	~Move0_Map();

	// delete Function
	Move0_Map(const Move0_Map& _Other) = delete;
	Move0_Map(Move0_Map&& _Other) noexcept = delete;
	Move0_Map& operator=(const Move0_Map& _Other) = delete;
	Move0_Map& operator=(Move0_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

