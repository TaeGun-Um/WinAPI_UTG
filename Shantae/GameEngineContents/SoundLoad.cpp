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
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\Title_Theme.mp3"));             // Opening BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\Title_announce.wav"));          // Opening ���� ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\File_Select.mp3"));             // Title BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\Botton_move.wav"));             // ���ù�ư ������ ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\Botton_select.wav"));           // ���ù�ư ���� ȿ����

	// Field
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Boss_Battle.mp3"));             // ������ BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\stage_clear.mp3"));             // Boss ���� ��
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\We_Love_Burning_Town.mp3"));    // FieldLevel BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\You_Found_an_item.mp3"));       // ���ڿ��� ������ ȹ�� ��
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explode_bridge.wav"));          // Boombridge �ٸ� ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explode_plat.wav"));            // Machinegun ���� ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explosion1.mp3"));              // Home, HouseFront, Move0 ���� ȯ���� 1
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explosion2.mp3"));              // Home, HouseFront, Move0 ���� ȯ���� 2
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Fleeing_crowd.mp3"));           // Move0 ����ġ�� ���ߵ�
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Housefront_bell.wav"));         // Home, HouseFront ���Ҹ� ȯ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Housefront_seagull1.wav"));     // Home, HouseFront ���ű� ȯ���� 1
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Housefront_seagull2.wav"));     // Home, HouseFront ���ű� ȯ���� 2
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Housefront_wave.wav"));         // Home, HouseFront �ĵ��Ҹ� ȯ����
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Clash_smalljar.wav"));			 // jar �ı� �� ȿ����

	// Town
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Scuttle_Town.mp3"));             // TownLevel BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Uncle_Room.mp3"));               // Uncle_Room BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Customer.mp3"));                 // Smith, Shop BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Sky.mp3"));                      // SkyRoom BGM

	// Ending
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Ending\\Ending.mp3"));                 // ���� ũ���� BGM

	////////////////////////////////////// Character //////////////////////////////////////
	GameEngineDirectory Dir1;
	Dir1.MoveParentToDirectory("Shantae_Resource");
	Dir1.Move("Shantae_Resource");
	Dir1.Move("Sound");
	Dir1.Move("Character");

	// Shatae
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_attack.wav"));         // ���� �� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_attack_voice1.wav"));  // ���� �� ���̽� 1
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_attack_voice2.wav"));  // ���� �� ���̽� 2
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Strike_enemy.wav"));          // ���� ���ݿ� �¾��� �� ȿ����

	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_move1.wav"));          // �̵� �� ȿ���� (��)
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_move2.wav"));          // �̵� �� ȿ���� (��)
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_crouch.mp3"));         // ��ũ����, ���� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_crouchmove.wav"));     // ��ũ���� �̵� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_death.wav"));          // �÷��̾� ��� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_fall.wav"));           // �÷��̾� ���� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hit1.wav"));           // �÷��̾� ���� �� ���̽� 1
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hit2.wav"));           // �÷��̾� ���� �� ���̽� 2
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_jump.wav"));           // ���� �� ���̽�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_land.wav"));           // ���� �� ���̽�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Splash_water.wav"));          // ���屸 ȿ����

	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Inventory_in.wav"));          // �κ��丮 ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Inventory_out.wav"));         // �κ��丮 �ݱ�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_bubble.wav"));         // ���� ��� ���̽�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_powerup.wav"));        // �Ŀ��� ��� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_pikeball.wav"));       // ����ũ�� ��� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_monstermilk.wav"));    // ���� ��ũ ��� ���̽�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_gem.wav"));            // �� ȹ�� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hp_large.wav"));       // ū ��Ʈ ȹ�� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hp_small.mp3"));       // ���� ��Ʈ ȹ�� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Store_purchase.wav"));        // ���� ������ ���� ȿ����
	
	// Soldier
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_die.wav"));                // Soldier ��� �� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_boom_explosion.mp3"));     // Bomberman ��ź ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_boom_throw.mp3"));         // Bomberman ��ź ������
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_gun_fire.mp3"));           // Black �Ѿ� �߻�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_machinegun_fire.mp3"));    // machinegun �Ѿ� �߻�
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Bridgeboom.wav"));                 // Bridgeboom �ð� ��� ȿ����

	// Boss
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Boom_blast.wav"));      // ��ź �߻� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Boom_bounce.mp3"));     // ��ź �ٿ ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Boss_fly.mp3"));        // ���� ƨ�ܳ��� �� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Boss_Run.mp3"));        // ���� ��ũ�� ������ �� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Explode_popcorn.wav")); // ���� ��� ��, ��ź ��Ʈ �� ȿ����
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Tank_Charge.mp3"));     // ��ũ ���� ȿ����

}

void SoundLoad::Update(float _DeltaTime)
{
}