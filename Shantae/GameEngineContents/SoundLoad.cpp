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
	////////////////////////////////////// Map //////////////////////////////////////
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("Shantae_Resource");
	Dir.Move("Shantae_Resource");
	Dir.Move("Sound");
	Dir.Move("Map");

	// Title
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\Title_Theme.mp3"));             // o Opening BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\Title_announce.wav"));          // o Opening ���� ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\File_Select.mp3"));             // o Title BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\Botton_move.wav"));             // o ���ù�ư ������ ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\Botton_select.wav"));           // o ���ù�ư ���� ȿ����

	// Field
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Boss_Battle.mp3"));             // o ������ BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\We_Love_Burning_Town.mp3"));    // o FieldLevel BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explode_bridge.wav"));          // o Boombridge �ٸ� ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explode_plat.wav"));            // o Machinegun ���� ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Fleeing_crowd.mp3"));           // o Move0 ����ġ�� ���ߵ�
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explosion1.mp3"));              // o Home, HouseFront, Move0 ���� ȯ���� 1
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explosion2.mp3"));              // o Home, HouseFront, Move0 ���� ȯ���� 2
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Housefront_bell.wav"));         // o Home, HouseFront ���Ҹ� ȯ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Housefront_seagull1.wav"));     // o Home, HouseFront ���ű� ȯ���� 1
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Housefront_seagull2.wav"));     // o Home, HouseFront ���ű� ȯ���� 2
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Housefront_wave.wav"));         // o Home, HouseFront �ĵ��Ҹ� ȯ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\House_explosion.mp3"));		 // o Home ������
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explosion_deep.wav"));			 // o �ǹ� ������
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Clash_smalljar.wav"));			 // o jar �ı� �� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Clash_bigjar.wav"));			 // o jar �ı� �� ȿ����

	// Town
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Scuttle_Town.mp3"));             // o TownLevel BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Uncle_Room.mp3"));               // o Uncle_Room BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Customer.mp3"));                 // o Smith, Shop BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Sky.mp3"));                      // o SkyRoom BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Smith.wav"));                    // o ���̽�
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\NextText.wav"));                 // o �ؽ�Ʈ

	// Ending
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Ending\\Ending.mp3"));                 // o ���� ũ���� BGM

	////////////////////////////////////// Character //////////////////////////////////////
	GameEngineDirectory Dir1;
	Dir1.MoveParentToDirectory("Shantae_Resource");
	Dir1.Move("Shantae_Resource");
	Dir1.Move("Sound");
	Dir1.Move("Character");

	// Shatae
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_attack.wav"));         // o ���� �� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_attack_voice1.wav"));  // o ���� �� ���̽� 1
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_attack_voice2.wav"));  // o ���� �� ���̽� 2
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Strike_enemy.mp3"));          // o ���� ���ݿ� �¾��� �� ȿ����

	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_move1.wav"));          // o �̵� �� ȿ���� 1  
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_move2.wav"));          // o �̵� �� ȿ���� 2
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_move3.wav"));          // o �̵� �� ȿ���� 3
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_crouch.mp3"));         // o ��ũ����, ���� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_crouchmove.wav"));     // o ��ũ���� �̵� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_death.wav"));          // �÷��̾� ��� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_fall.wav"));           // �÷��̾� ���� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hit1.wav"));           // o �÷��̾� ���� �� ���̽� 1
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hit2.wav"));           // o �÷��̾� ���� �� ���̽� 2
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hit3.wav"));           // o �÷��̾� ���� �� ���̽� 3
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hit4.wav"));           // o �÷��̾� ���� �� ���̽� 4
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hit5.wav"));           // o �÷��̾� ���� �� ���̽� 5
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_jump.wav"));           // o ���� �� ���̽�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_land.wav"));           // o ���� �� ���̽�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Splash_water.wav"));          // o ���屸 ȿ����

	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Inventory_in.wav"));          // o �κ��丮 ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Inventory_out.wav"));         // o �κ��丮 �ݱ�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_bubble.wav"));         // o ���� ��� ���̽�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_pikeball.wav"));       // o ����ũ�� ��� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_monstermilk.wav"));    // o ���� ��ũ ��� ���̽�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_gem.wav"));            // o �� ȹ�� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hp_large.wav"));       // o ū ��Ʈ ȹ�� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hp_small.mp3"));       // o ���� ��Ʈ ȹ�� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Store_purchase.wav"));        // o ���� ������ ���� ȿ����
	
	// Soldier
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_die.wav"));                // o Soldier ��� �� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_boom_explosion.mp3"));     // o Bomberman ��ź ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_boom_throw.mp3"));         // o Bomberman ��ź ������
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_gun_fire.mp3"));           // o Black �Ѿ� �߻�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_machinegun_fire.mp3"));    // o machinegun �Ѿ� �߻�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Bridgeboom.wav"));                 // o Bridgeboom �ð� ��� ȿ����

	// Boss
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Boom_blast.wav"));      // o ��ź �߻� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Boom_bounce.mp3"));     // o ��ź �ٿ ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Boss_fly.mp3"));        // o ���� ƨ�ܳ��� �� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Boss_Run.mp3"));        // o ���� ��ũ�� ������ �� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Explode_popcorn.wav")); // o ���� ��� ��, ��ź ��Ʈ �� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Tank_Charge.mp3"));     // o ��ũ ���� ȿ����

	// mermaid
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Mermaid\\mermaid_bubble.wav")); // o
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Mermaid\\mermaid_death.wav"));  // o
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Mermaid\\mermaid_hurt.wav"));   // o
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Mermaid\\mermaid_jump.wav"));   // o

}

void SoundLoad::Update(float _DeltaTime)
{
}