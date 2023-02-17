#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Move1 Map
class Move1_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Move1_Map();
	~Move1_Map();

	// delete Function
	Move1_Map(const Move1_Map& _Other) = delete;
	Move1_Map(Move1_Map&& _Other) noexcept = delete;
	Move1_Map& operator=(const Move1_Map& _Other) = delete;
	Move1_Map& operator=(Move1_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

