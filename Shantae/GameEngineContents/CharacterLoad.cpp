#include "CharacterLoad.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>

CharacterLoad::CharacterLoad()
{
}

CharacterLoad::~CharacterLoad()
{
}

void CharacterLoad::Loading()
{
	// °æ·Î
	Dir.MoveParentToDirectory("Shantae_Resource");
	Dir.Move("Shantae_Resource");
	Dir.Move("Image");
	Dir.Move("Character");

	//////////////////////////////// Player ////////////////////////////////
	// Shantae
	GameEngineImage* Image0 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Shantae\\Shantae_R.bmp"));
	Image0->Cut(5, 87);
	GameEngineImage* Image1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Shantae\\Shantae_L.bmp"));
	Image1->Cut(5, 87);

	//////////////////////////////// Monster ////////////////////////////////
	// Soldier
	GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Blue_L.BMP"));
	Image2->Cut(5, 9);
	GameEngineImage* Image3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Blue_R.BMP"));
	Image3->Cut(5, 9);
	GameEngineImage* Image4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Red_L.BMP"));
	Image4->Cut(5, 5);
	GameEngineImage* Image5 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Red_R.BMP"));
	Image5->Cut(5, 5);
	GameEngineImage* Image6 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Black_L.BMP"));
	Image6->Cut(5, 5);
	GameEngineImage* Image7 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Black_R.BMP"));
	Image7->Cut(5, 5);
	GameEngineImage* Image8 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Spider_L.BMP"));
	Image8->Cut(5, 4);
	GameEngineImage* Image9 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Spider_R.BMP"));
	Image9->Cut(5, 4);
	GameEngineImage* Image10 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Machinegun_L.BMP"));
	Image10->Cut(5, 4);
	GameEngineImage* Image11 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Machinegun_R.BMP"));
	Image11->Cut(5, 4);
	GameEngineImage* Image12 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Boom_L.BMP"));
	Image12->Cut(12, 1);
	GameEngineImage* Image13 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Boom_R.BMP"));
	Image13->Cut(12, 1);
	GameEngineImage* Image14 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Bullet.BMP"));
	Image14->Cut(2, 1);
	GameEngineImage* Image15 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Machinegun_Bulletmarks.BMP"));
	Image15->Cut(12, 1);
	GameEngineImage* Image16 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Aim.BMP"));
	Image16->Cut(2, 1);
	GameEngineImage* Image1666 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Soldier\\Soldier_Pile.BMP"));
	Image1666->Cut(2, 12);

	// Boos
	GameEngineImage* Image17 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Boss\\AmmoBaron_L.BMP"));
	Image17->Cut(5, 15);
	GameEngineImage* Image18 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Boss\\AmmoBaron_R.BMP"));
	Image18->Cut(5, 15);
	GameEngineImage* Image19 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Boss\\Boss_Tank.BMP"));
	Image19->Cut(5, 8);

	// Scarecrow
	GameEngineImage* Image20 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Scarecrow\\Scarecrow_L.BMP"));
	Image20->Cut(5, 12);
	GameEngineImage* Image21 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Scarecrow\\Scarecrow_R.BMP"));
	Image21->Cut(5, 12);
	GameEngineImage* Image22 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Scarecrow\\Scarecrow_Pumpkine_L.BMP"));
	Image22->Cut(8, 1);
	GameEngineImage* Image23 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Scarecrow\\Scarecrow_Pumpkine_R.BMP"));
	Image23->Cut(8, 1);
	GameEngineImage* Image24 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Scarecrow\\Scarecrow_PumpkineBoom_L.BMP"));
	Image24->Cut(6, 1);
	GameEngineImage* Image25 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Scarecrow\\Scarecrow_PumpkineBoom_R.BMP"));
	Image25->Cut(6, 1);
	GameEngineImage* Image26 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Scarecrow\\Scarecrow_Black_L.BMP"));
	Image26->Cut(5, 13);
	GameEngineImage* Image27 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Scarecrow\\Scarecrow_Black_R.BMP"));
	Image27->Cut(5, 13);
	GameEngineImage* Image28 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Scarecrow\\Scarecrow_Black_Fire_L.BMP"));
	Image28->Cut(15, 1);
	GameEngineImage* Image29 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Scarecrow\\Scarecrow_Black_Fire_R.BMP"));
	Image29->Cut(15, 1);

	// Mermaid
	GameEngineImage* Image30 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Mermaid\\Mermaid_L.BMP"));
	Image30->Cut(5, 21);
	GameEngineImage* Image31 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Mermaid\\Mermaid_R.BMP"));
	Image31->Cut(5, 21);
	GameEngineImage* Image32 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Mermaid\\Mermaid_Heart_L.BMP"));
	Image32->Cut(8, 1);
	GameEngineImage* Image33 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Mermaid\\Mermaid_Heart_R.BMP"));
	Image33->Cut(8, 1);
	GameEngineImage* Image34 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Mermaid\\Mermaid_Attack.BMP"));
	Image34->Cut(4, 1);
	GameEngineImage* Image35 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Mermaid\\Mermaid_AttackBoom.BMP"));
	Image35->Cut(6, 1);
	
	// Public
	GameEngineImage* Image36 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Public\\Public_Boom.BMP"));
	Image36->Cut(12, 1);
	GameEngineImage* Image37 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Public\\Bridge_Boom.BMP"));
	Image37->Cut(3, 1);
	GameEngineImage* Image38 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Public\\Misillie.BMP"));

	// Bat
	GameEngineImage* Image39 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Bat\\Bat_R.BMP"));
	Image39->Cut(5, 10);
	GameEngineImage* Image40 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Bat\\Bat_L.BMP"));
	Image40->Cut(5, 10);

	// Spider
	GameEngineImage* Image41 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Spider\\Spider.BMP"));
	Image41->Cut(5, 7);

	//////////////////////////////// NPC ////////////////////////////////
}
