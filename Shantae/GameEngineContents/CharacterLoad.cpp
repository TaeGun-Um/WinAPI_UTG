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
	GameEngineImage* Image1010 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Shantae\\Splash.bmp"));
	Image1010->Cut(9, 1);
	GameEngineImage* Image0101 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Shantae\\Impact.bmp"));
	Image0101->Cut(6, 1);
	GameEngineImage* Image1111 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Shantae\\Pistol_Bullet.bmp"));
	Image1111->Cut(6, 1);

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
	GameEngineImage* Image199 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Boss\\SmallPoof.BMP"));
	Image199->Cut(6, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Boss\\Boom_Red.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Boss\\Boom_Black.BMP"));

	// Scarecrow
	GameEngineImage* Image20 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Scarecrow\\Scarecrow_L.BMP"));
	Image20->Cut(5, 12);
	GameEngineImage* Image21 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Scarecrow\\Scarecrow_R.BMP"));
	Image21->Cut(5, 12);

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

	// Cacklebat
	GameEngineImage* Image41 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Cacklebat\\Cacklebat_L.BMP"));
	Image41->Cut(5, 11);
	GameEngineImage* Image42 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster\\Cacklebat\\Cacklebat_R.BMP"));
	Image42->Cut(5, 11);

	//////////////////////////////// NPC ////////////////////////////////

	GameEngineImage* Image43 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Bathwoman.BMP"));
	Image43->Cut(11, 1);
	GameEngineImage* Image44 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Boy_L.BMP"));
	Image44->Cut(5, 5);
	GameEngineImage* Image45 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Boy_R.BMP"));
	Image45->Cut(5, 5);
	GameEngineImage* Image46 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Dancer_L.BMP"));
	Image46->Cut(5, 2);
	GameEngineImage* Image47 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Dancer_R.BMP"));
	Image47->Cut(5, 2);
	GameEngineImage* Image48 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Desert Man_L.BMP"));
	Image48->Cut(5, 6);
	GameEngineImage* Image49 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Desert Man_R.BMP"));
	Image49->Cut(5, 6);
	GameEngineImage* Image50 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Girl_L.BMP"));
	Image50->Cut(5, 5);
	GameEngineImage* Image51 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Girl_R.BMP"));
	Image51->Cut(5, 5);
	GameEngineImage* Image52 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Jug Woman_L.BMP"));
	Image52->Cut(5, 6);
	GameEngineImage* Image53 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Jug Woman_R.BMP"));
	Image53->Cut(5, 6);
	GameEngineImage* Image54 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Mayor Scuttlebutt_L.BMP"));
	Image54->Cut(5, 2);
	GameEngineImage* Image55 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Mayor Scuttlebutt_R.BMP"));
	Image55->Cut(5, 2);
	GameEngineImage* Image56 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Merchant.BMP"));
	Image56->Cut(5, 2);
	GameEngineImage* Image57 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Sailor_L.BMP"));
	Image57->Cut(5, 3);
	GameEngineImage* Image58 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Sailor_R.BMP"));
	Image58->Cut(5, 3);
	GameEngineImage* Image59 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Sky_L.BMP"));
	Image59->Cut(5, 9);
	GameEngineImage* Image60 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Sky_R.BMP"));
	Image60->Cut(5, 9);
	GameEngineImage* Image61 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Squidsmith_L.BMP"));
	Image61->Cut(5, 18);
	GameEngineImage* Image611 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Squidsmith_R.BMP"));
	Image611->Cut(5, 18);
	GameEngineImage* Image62 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Stylist_L.BMP"));
	Image62->Cut(5, 4);
	GameEngineImage* Image63 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Stylist_R.BMP"));
	Image63->Cut(5, 4);
	GameEngineImage* Image64 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Town Guard_L.BMP"));
	Image64->Cut(5, 3);
	GameEngineImage* Image65 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Town Guard_R.BMP"));
	Image65->Cut(5, 3);
	GameEngineImage* Image66 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NPC\\Wrench.BMP"));
	Image66->Cut(5, 5);

}
