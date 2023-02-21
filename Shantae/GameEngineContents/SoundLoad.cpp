#include "SoundLoad.h"

#include <GameEngineCore/GameEngineResources.h>

SoundLoad::SoundLoad() 
{
}

SoundLoad::~SoundLoad() 
{
}

void SoundLoad::Loading()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("Shantae_Resource");
	Dir.Move("Shantae_Resource");
	Dir.Move("Sound");
	Dir.Move("Map");

	// Title
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\File_Select.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\Title_Theme.mp3"));

	// Field
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Boss_Battle.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\stage_clear.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\We_Love_Burning_Town.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\You_Found_an_item.mp3"));

	// Town
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Customer.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Scuttle_Town.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Sky.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Uncle_Room.mp3"));

	// Ending
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Ending\\Ending.mp3"));

	// Test

	GameEngineDirectory Dir1;
	Dir1.MoveParentToDirectory("Shantae_Resource");
	Dir1.Move("Shantae_Resource");
	Dir1.Move("Sound");
	Dir1.Move("Character");

	// Shatae

	// Soldier

	// 
}

void SoundLoad::Update(float _DeltaTime)
{
}