#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Shop_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	Shop_Sky();
	~Shop_Sky();

	// delete Function
	Shop_Sky(const Shop_Sky& _Other) = delete;
	Shop_Sky(Shop_Sky&& _Other) noexcept = delete;
	Shop_Sky& operator=(const Shop_Sky& _Other) = delete;
	Shop_Sky& operator=(Shop_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

