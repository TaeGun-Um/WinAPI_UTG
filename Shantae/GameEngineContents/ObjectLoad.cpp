#include "ObjectLoad.h"

#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineResources.h>

#include "MonsterSpawner.h"

ObjectLoad* ObjectLoad::ObjectLoadPtr = nullptr;

ObjectLoad::ObjectLoad() 
{
}

ObjectLoad::~ObjectLoad() 
{
}

void ObjectLoad::Loading()
{
	ObjectLoadPtr = this;

	// 경로
	Dir.MoveParentToDirectory("Shantae_Resource");
	Dir.Move("Shantae_Resource");
	Dir.Move("Image");
	Dir.Move("Map");

	//////////////////////////////// Object ////////////////////////////////

	// Test
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Test\\AnimationBox_Idle.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Test\\AnimationBox_Run.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Test\\AnimationBox_Spot.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Test\\AnimationBox_Jump.bmp"));

	// Title
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Title\\Opening_Background.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Title\\SelectMenu_Background.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Title\\SelectMenu_Button_Start.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Title\\SelectMenu_Button_Test.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Title\\SelectMenu_Button_End.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Title\\SelectMenu_Icon.BMP"));



	//////////////////////////////// Field ////////////////////////////////
	// Public
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Public\\Building0.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Public\\Building1.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Public\\Building2.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Public\\Ship.bmp"));
	 
	// House
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\House\\House_Hut.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\House\\House_interior.bmp"));

	// HouseFront
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\HouseFront\\HouseFront_Map.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\HouseFront\\HouseFront_Building.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\HouseFront\\HouseFront_Bush.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\HouseFront\\HouseFront_Island.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\HouseFront\\HouseFront_LightHouse.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\HouseFront\\HouseFront_PalmTree.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\HouseFront\\HouseFront_Sea.bmp"));

	// Move0
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Move0\\Move0_Buliding.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Move0\\Move0_Bush.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Move0\\Move0_Map.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Move0\\Move0_Sea.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Move0\\Move0_Sky.bmp"));

	// Move1
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Move1\\Move1_Buliding.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Move1\\Move1_Bush.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Move1\\Move1_Map.bmp"));

	// Stair
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Stair\\Stair_Bush1.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Stair\\Stair_Bush2.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Stair\\Stair_Map.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Stair\\Stair_Stair.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Stair\\Stair_Tower.bmp"));

	// Machinegun
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Machinegun\\Machinegun_Background.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Machinegun\\Machinegun_Map.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Machinegun\\Machinegun_Plat.bmp"));

	// BoomBridge
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\BoomBridge\\BoomBridge_Background.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\BoomBridge\\BoomBridge_Map.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\BoomBridge\\BoomBridge_Bridge1.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\BoomBridge\\BoomBridge_Bridge2.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\BoomBridge\\BoomBridge_Bridge3.bmp"));

	// BeforeBoss
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\BeforeBoss\\BeforeBoss_Background.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\BeforeBoss\\BeforeBoss_Map.bmp"));

	// Boss
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Boss\\Boss_Map.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Boss\\Boss_Bush1.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Boss\\Boss_Bush2.bmp"));

	//////////////////////////////// Town ////////////////////////////////

	// Scuttle
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Scuttle\\Scuttle_Background.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Scuttle\\Scuttle_Map.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Scuttle\\Scuttle_Sky.bmp"));

	// UncleRoom
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\UncleRoom\\UncleRoom_Background.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\UncleRoom\\UncleRoom_Front.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\UncleRoom\\UncleRoom_Map.bmp"));

	// Shop
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Shop\\Shop_Background.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Shop\\Shop_Front.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Shop\\Shop_Map.bmp"));

	
	// Spa
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Spa\\Spa_Background.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Spa\\Spa_Map.bmp"));

	// Smith
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Smith\\Smith_Background.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Smith\\Smith_Map.bmp"));

	
	// SkyRoom
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\SkyRoom\\SkyRoom_Background.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\SkyRoom\\SkyRoom_Map.bmp"));

	// SaveRoom
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\SaveRoom\\SaveRoom_Background.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\SaveRoom\\SaveRoom_Front.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\SaveRoom\\SaveRoom_Front2.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\SaveRoom\\SaveRoom_Map.bmp"));

	AnmationObjectLoad();
	ColMapLoad();
}

void ObjectLoad::AnmationObjectLoad()
{
	GameEngineImage* Image1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\House\\Shantae_Pajamas.bmp"));
	Image1->Cut(5, 14);

	GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\HouseFront\\HouseFront_WindVane.bmp"));
	Image2->Cut(14, 1);
}

void ObjectLoad::ColMapLoad()
{
	// Test
	Test = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Test\\TestMap.bmp"));

	// Field
	HouseFront = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\HouseFront\\HouseFront_ColMap.bmp"));
	Move0 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Move0\\Move0_ColMap.bmp"));
	Move1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Move1\\Move1_ColMap.bmp"));
	Stair = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Stair\\Stair_ColMap.bmp"));
	Machinegun = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Machinegun\\Machinegun_ColMap.bmp"));
	BoomBridge = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\BoomBridge\\BoomBridge_ColMap.bmp"));
	BeforeBoss = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\BeforeBoss\\BeforeBoss_ColMap.bmp"));
	Boss = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Field\\Boss\\Boss_ColMap.bmp"));

	// Town
	Scuttle = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Scuttle\\Scuttle_ColMap.bmp"));
	UncleRoom = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\UncleRoom\\UncleRoom_ColMap.bmp"));
	Shop = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Shop\\Shop_ColMap.bmp"));
	Spa = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Spa\\Spa_ColMap.bmp"));
	Smith = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\Smith\\Smith_ColMap.bmp"));
	SkyRoom = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\SkyRoom\\SkyRoom_ColMap.bmp"));
	SaveRoom = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Town\\SaveRoom\\SaveRoom_ColMap.bmp"));
}

GameEngineImage* ObjectLoad::GetColMap(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (GameEngineString::ToUpper("Test") == UpperName)
	{
		return Test;
	}
	else if (GameEngineString::ToUpper("HouseFront") == UpperName)
	{
		return HouseFront;
	}
	else if (GameEngineString::ToUpper("Move0") == UpperName)
	{
		return Move0;
	}
	else if (GameEngineString::ToUpper("Move1") == UpperName)
	{
		return Move1;
	}
	else if (GameEngineString::ToUpper("Stair") == UpperName)
	{
		return Stair;
	}
	else if (GameEngineString::ToUpper("Machinegun") == UpperName)
	{
		return Machinegun;
	}
	else if (GameEngineString::ToUpper("BoomBridge") == UpperName)
	{
		return BoomBridge;
	}
	else if (GameEngineString::ToUpper("BeforeBoss") == UpperName)
	{
		return BeforeBoss;
	}
	else if (GameEngineString::ToUpper("Boss") == UpperName)
	{
		return Boss;
	}
	else if (GameEngineString::ToUpper("Scuttle") == UpperName)
	{
		return Scuttle;
	}
	else if (GameEngineString::ToUpper("UncleRoom") == UpperName)
	{
		return UncleRoom;
	}
	else if (GameEngineString::ToUpper("Shop") == UpperName)
	{
		return Shop;
	}
	else if (GameEngineString::ToUpper("Spa") == UpperName)
	{
		return Spa;
	}
	else if (GameEngineString::ToUpper("Smith") == UpperName)
	{
		return Smith;
	}
	else if (GameEngineString::ToUpper("SkyRoom") == UpperName)
	{
		return SkyRoom;
	}
	else if (GameEngineString::ToUpper("SaveRoom") == UpperName)
	{
		return SaveRoom;
	}
	else
	{
		MsgAssert("올바른 ColMapName을 넣어주세요." + UpperName);
		return 0;
	}
}