#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Shop_Sea : public GameEngineActor
{
public:
	// constrcuter destructer
	Shop_Sea();
	~Shop_Sea();

	// delete Function
	Shop_Sea(const Shop_Sea& _Other) = delete;
	Shop_Sea(Shop_Sea&& _Other) noexcept = delete;
	Shop_Sea& operator=(const Shop_Sea& _Other) = delete;
	Shop_Sea& operator=(Shop_Sea&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

