#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Shop_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Shop_Map();
	~Shop_Map();

	// delete Function
	Shop_Map(const Shop_Map& _Other) = delete;
	Shop_Map(Shop_Map&& _Other) noexcept = delete;
	Shop_Map& operator=(const Shop_Map& _Other) = delete;
	Shop_Map& operator=(Shop_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

