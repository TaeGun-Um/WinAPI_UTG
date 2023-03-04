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
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\Title_announce.wav"));          // o Opening 샨테 음성
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\File_Select.mp3"));             // o Title BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\Botton_move.wav"));             // o 선택버튼 움직임 효과음
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title\\Botton_select.wav"));           // o 선택버튼 선택 효과음

	// Field
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Boss_Battle.mp3"));             // o 보스전 BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\We_Love_Burning_Town.mp3"));    // o FieldLevel BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explode_bridge.wav"));          // o Boombridge 다리 폭파
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explode_plat.wav"));            // o Machinegun 발판 폭파
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Fleeing_crowd.mp3"));           // o Move0 도망치는 관중들
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explosion1.mp3"));              // o Home, HouseFront, Move0 폭파 환경음 1
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explosion2.mp3"));              // o Home, HouseFront, Move0 폭파 환경음 2
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Housefront_bell.wav"));         // o Home, HouseFront 종소리 환경음
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Housefront_seagull1.wav"));     // o Home, HouseFront 갈매기 환경음 1
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Housefront_seagull2.wav"));     // o Home, HouseFront 갈매기 환경음 2
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Housefront_wave.wav"));         // o Home, HouseFront 파도소리 환경음
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\House_explosion.mp3"));		 // o Home 폭발음
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Explosion_deep.wav"));			 // o 건물 폭발음
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Clash_smalljar.wav"));			 // o jar 파괴 시 효과음
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Field\\Clash_bigjar.wav"));			 // o jar 파괴 시 효과음

	// Town
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Scuttle_Town.mp3"));             // o TownLevel BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Uncle_Room.mp3"));               // o Uncle_Room BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Customer.mp3"));                 // o Smith, Shop BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Sky.mp3"));                      // o SkyRoom BGM
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\Smith.wav"));                    // o 스미스
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Town\\NextText.wav"));                 // o 텍스트

	// Ending
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Ending\\Ending.mp3"));                 // o 엔딩 크레딧 BGM

	////////////////////////////////////// Character //////////////////////////////////////
	GameEngineDirectory Dir1;
	Dir1.MoveParentToDirectory("Shantae_Resource");
	Dir1.Move("Shantae_Resource");
	Dir1.Move("Sound");
	Dir1.Move("Character");

	// Shatae
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_attack.wav"));         // o 공격 시 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_attack_voice1.wav"));  // o 공격 시 보이스 1
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_attack_voice2.wav"));  // o 공격 시 보이스 2
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Strike_enemy.mp3"));          // o 적이 공격에 맞았을 때 효과음

	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_move1.wav"));          // o 이동 시 효과음 1  
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_move2.wav"));          // o 이동 시 효과음 2
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_move3.wav"));          // o 이동 시 효과음 3
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_crouch.mp3"));         // o 웅크리기, 랜딩 효과임
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_crouchmove.wav"));     // o 웅크리기 이동 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_death.wav"));          // 플레이어 사망 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_fall.wav"));           // 플레이어 낙사 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hit1.wav"));           // o 플레이어 맞을 시 보이스 1
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hit2.wav"));           // o 플레이어 맞을 시 보이스 2
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hit3.wav"));           // o 플레이어 맞을 시 보이스 3
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hit4.wav"));           // o 플레이어 맞을 시 보이스 4
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hit5.wav"));           // o 플레이어 맞을 시 보이스 5
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_jump.wav"));           // o 점프 시 보이스
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_land.wav"));           // o 랜딩 시 보이스
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Splash_water.wav"));          // o 물장구 효과음

	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Inventory_in.wav"));          // o 인벤토리 오픈
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Inventory_out.wav"));         // o 인벤토리 닫기
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_bubble.wav"));         // o 버블 사용 보이스
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_pikeball.wav"));       // o 파이크볼 사용 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_monstermilk.wav"));    // o 몬스터 밀크 사용 보이스
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_gem.wav"));            // o 젬 획득 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hp_large.wav"));       // o 큰 하트 획득 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Player_hp_small.mp3"));       // o 작은 하트 획득 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Shantae\\Store_purchase.wav"));        // o 상점 아이템 구매 효과음
	
	// Soldier
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_die.wav"));                // o Soldier 사망 시 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_boom_explosion.mp3"));     // o Bomberman 폭탄 폭파
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_boom_throw.mp3"));         // o Bomberman 폭탄 던지기
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_gun_fire.mp3"));           // o Black 총알 발사
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Soldier_machinegun_fire.mp3"));    // o machinegun 총알 발사
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Soldier\\Bridgeboom.wav"));                 // o Bridgeboom 시간 경과 효과음

	// Boss
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Boom_blast.wav"));      // o 폭탄 발사 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Boom_bounce.mp3"));     // o 폭탄 바운스 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Boss_fly.mp3"));        // o 보스 튕겨나올 때 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Boss_Run.mp3"));        // o 보스 탱크로 복귀할 때 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Explode_popcorn.wav")); // o 보스 사망 시, 폭탄 히트 시 효과음
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Boss\\Tank_Charge.mp3"));     // o 탱크 차지 효과음

	// mermaid
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Mermaid\\mermaid_bubble.wav")); // o
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Mermaid\\mermaid_death.wav"));  // o
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Mermaid\\mermaid_hurt.wav"));   // o
	GameEngineResources::GetInst().SoundLoad(Dir1.GetPlusFileName("Monster\\Mermaid\\mermaid_jump.wav"));   // o

}

void SoundLoad::Update(float _DeltaTime)
{
}