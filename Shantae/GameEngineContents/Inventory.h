#pragma once

#include <map>

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class ItemSelect;

// Ό³Έν :
class Inventory : public GameEngineActor
{
public:
	static Inventory* PlayerInven;

	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

	GameEngineRender* AnimationRender = nullptr;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void SelectMove(float _DeltaTime);

	ItemSelect* Select = nullptr;

	GameEngineSoundPlayer BGMPlayer;
	// std::map<int, ItemBox*> AllBox;

	int SelectCreate = 1;

};

//class ItemBox
//{
//public:
//
//	friend Inventory;
//
//	// constrcuter destructer
//	ItemBox();
//	~ItemBox();
//
//	// delete Function
//	ItemBox(const ItemBox& _Other) = delete;
//	ItemBox(ItemBox&& _Other) noexcept = delete;
//	ItemBox& operator=(const ItemBox& _Other) = delete;
//	ItemBox& operator=(ItemBox&& _Other) noexcept = delete;
//
//protected:
//
//private:
//	int BoxNumber = 1;
//	float4 BoxPos = float4::Zero;
//
//};