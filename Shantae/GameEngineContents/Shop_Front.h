#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Shop_Front : public GameEngineActor
{
public:
	// constrcuter destructer
	Shop_Front();
	~Shop_Front();

	// delete Function
	Shop_Front(const Shop_Front& _Other) = delete;
	Shop_Front(Shop_Front&& _Other) noexcept = delete;
	Shop_Front& operator=(const Shop_Front& _Other) = delete;
	Shop_Front& operator=(Shop_Front&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

