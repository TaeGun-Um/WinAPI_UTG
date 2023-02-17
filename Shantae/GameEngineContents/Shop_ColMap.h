#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 바다 위 섬
class Shop_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;

	// constrcuter destructer
	Shop_ColMap();
	~Shop_ColMap();

	// delete Function
	Shop_ColMap(const Shop_ColMap& _Other) = delete;
	Shop_ColMap(Shop_ColMap&& _Other) noexcept = delete;
	Shop_ColMap& operator=(const Shop_ColMap& _Other) = delete;
	Shop_ColMap& operator=(Shop_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

