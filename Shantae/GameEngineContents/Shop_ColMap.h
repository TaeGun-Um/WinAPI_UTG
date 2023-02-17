#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : HouseFront�� �ٴ� �� ��
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

