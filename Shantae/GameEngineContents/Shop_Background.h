#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Shop_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	Shop_Background();
	~Shop_Background();

	// delete Function
	Shop_Background(const Shop_Background& _Other) = delete;
	Shop_Background(Shop_Background&& _Other) noexcept = delete;
	Shop_Background& operator=(const Shop_Background& _Other) = delete;
	Shop_Background& operator=(Shop_Background&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

