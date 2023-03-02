#pragma once

#include <map>

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class ItemSelect;
class Icon;

class ItemSpace
{
public:
	// constrcuter destructer
	ItemSpace();
	~ItemSpace();

	// delete Function
	ItemSpace(const ItemSpace& _Other) = delete;
	ItemSpace(ItemSpace&& _Other) noexcept = delete;
	ItemSpace& operator=(const ItemSpace& _Other) = delete;
	ItemSpace& operator=(ItemSpace&& _Other) noexcept = delete;

	void SetBoxNumber(int _Value)
	{
		BoxNumber = _Value;
	}

	void SetBoxPos(float4 _Pos)
	{
		BoxPos = _Pos;
	}

	float4 GetBoxPos()
	{
		return BoxPos;
	}

	Icon* GetItemIcon()
	{
		return ItemIcon;
	}

	void SetItemIcon(Icon* _Icon)
	{
		ItemIcon = _Icon;
	}

private:
	int BoxNumber = 1;
	float4 BoxPos = float4::Zero;
	Icon* ItemIcon = nullptr;
};

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

	void SetEquipItem(std::string_view _Equip)
	{
		EquipItem = _Equip;
	}

	std::map<int, ItemSpace*>* GetBoxes()
	{
		return &Boxes;
	}

	void DataCopy(Inventory* _Other);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void ItemSpaceSetting();
	void FamilyOn();
	void FamilyOff();
	void SetItemBox(int _Order, float4 _BoxPos);
	void CreateItem(std::string_view _Name);
	Icon* SelectItem();
	void PlayerItemCheck();
	void SelectMove(float _DeltaTime);

	ItemSelect* Select = nullptr;
	std::map<int, ItemSpace*> Boxes;

	GameEngineSoundPlayer BGMPlayer;

	std::string_view EquipItem = "Meat";

	float4 BoxPos = float4::Zero;

	float XPos = 0.0f;
	float YPos = 0.0f;

	int SelectCreate = 1;
	int BoxNumber = 0;
	
	bool LeftMove = false;

};
