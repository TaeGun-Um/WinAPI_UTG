#include "InventoryData.h"

InventoryData* InventoryData::InvenData = nullptr;

InventoryData::InventoryData() 
{
	InvenData = this;
	Data = std::map<int, ItemSpace*>();
}

InventoryData::~InventoryData() 
{
}