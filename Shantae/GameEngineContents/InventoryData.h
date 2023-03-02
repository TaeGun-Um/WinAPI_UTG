#pragma once

#include <map>

class Inventory;
class ItemSpace;

// Ό³Έν :
class InventoryData
{
public:
	static InventoryData* InvenData;

	// constrcuter destructer
	InventoryData();
	~InventoryData();

	// delete Function
	InventoryData(const InventoryData& _Other) = delete;
	InventoryData(InventoryData&& _Other) noexcept = delete;
	InventoryData& operator=(const InventoryData& _Other) = delete;
	InventoryData& operator=(InventoryData&& _Other) noexcept = delete;

	void SetInventoryDate(std::map<int, ItemSpace*> _Data)
	{
		Data.merge(_Data);
	}

	std::map<int, ItemSpace*> GetInventoryDate()
	{
		return Data;
	}

protected:

private:
	std::map<int, ItemSpace*> Data;
	
};

