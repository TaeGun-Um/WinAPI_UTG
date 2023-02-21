
// Core
#include "ShantaeCore.h"

// TitleLevel
#include "Opening.h"           // 오프닝
#include "SelectMeun.h"        // 게임 선택창

//FieldLevel
#include "House.h"             // Field_1
#include "HouseFront.h"	       // Field_2
#include "Move0.h"		       // Field_3
#include "Move1.h"		       // Field_4
#include "Stair.h"		       // Field_5
#include "Machinegun.h"	       // Field_6
#include "BoomBridge.h"	       // Field_7
#include "BeforeBoss.h"	       // Field_9
#include "Boss.h"		       // Field_10

//TownLevel
#include "Scuttle.h"
#include "UncleRoom.h"
#include "Shop.h"
#include "Spa.h"
#include "Smith.h"
#include "SkyRoom.h"
#include "SaveRoom.h"

//EndingLevel

// TestLevel
#include "TestLevel.h"

//ETC
#include "CharacterLoad.h"
#include "ObjectLoad.h"
#include "SoundLoad.h"
#include "KeyLoad.h"
#include "UILoad.h"

ShantaeCore ShantaeCore::Core;

ShantaeCore::ShantaeCore()
{
}

ShantaeCore::~ShantaeCore() 
{
}

void ShantaeCore::Start()
{
	// 의도릭
	int* a = new int;

// ------------------------------- 레벨 생성(동적할당) -------------------------------
	// ETC
	CreateLevel<KeyLoad>("KeyLoad");
	CreateLevel<UILoad>("UILoad");
	CreateLevel<ObjectLoad>("ObjectLoad");
	CreateLevel<CharacterLoad>("CharacterLoad");
	CreateLevel<SoundLoad>("SoundLoad");
	CreateLevel<PlayLevel>("PlayLevel");

	// TitleLevel
	CreateLevel<Opening>("Opening");
	CreateLevel<SelectMeun>("SelectMeun");

	// FieldLevel
	CreateLevel<House>("House");
	CreateLevel<HouseFront>("HouseFront");
	CreateLevel<Move0>("Move0");
	CreateLevel<Move1>("Move1");
	CreateLevel<Stair>("Stair");
	CreateLevel<Machinegun>("Machinegun");
	CreateLevel<BoomBridge>("BoomBridge");
	CreateLevel<BeforeBoss>("BeforeBoss");
	CreateLevel<Boss>("Boss");

	// TownLevel
	CreateLevel<Scuttle>("Scuttle");
	CreateLevel<UncleRoom>("UncleRoom");
	CreateLevel<Shop>("Shop");
	CreateLevel<Spa>("Spa");
	CreateLevel<Smith>("Smith");
	CreateLevel<SkyRoom>("SkyRoom");
	CreateLevel<SaveRoom>("SaveRoom");

	// EndingLevel

	// TestLevel
	CreateLevel<TestLevel>("TestLevel");

// ------------------------------- 레벨 선택 -------------------------------
	ChangeLevel("Move0");
}

void ShantaeCore::Update()
{
}

void ShantaeCore::End()
{
}