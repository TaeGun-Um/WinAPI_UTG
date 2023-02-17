#include "Move0.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Move0_Buliding.h"
#include "Move0_ColMap.h"
#include "Move0_Map.h"
#include "Move0_Sea.h"
#include "Move0_Sky.h"
#include "Move0_ETCBackground.h"
#include "Player.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"

GameEngineSoundPlayer Move0::FieldBGMPlayer = 0;

Move0::Move0() 
{
}

Move0::~Move0() 
{
}

void Move0::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Move0");

	// Background(����)
	CreateActor<Move0_Sky>();
	CreateActor<Move0_Sea>();
	CreateActor<Move0_ETCBackground>();
	CreateActor<Move0_Buliding>();

	// Map
	CreateActor<Move0_Map>();
	CreateActor<Move0_ColMap>();

	// Monster
	// �����ʻ���   ������ ��ġ    ���̸�    �ݸ�    �� �� ��ġ   �����ð�
	// CreateSpawner({ 250, 300 }, "blue", ColMap, { 350, 590 }, 5);

	CreateSpawner({ 1860, 0 }, "blue", ColMap, { 3251, 345 }, 5);
	CreateSpawner({ 3852, 0 }, "blue", ColMap, { 4821, 294 }, 5);
	CreateSpawner({ 4423, 0 }, "blue", ColMap, { 5400, 640 }, 5);
	MonsterSpawner* s1 = CreateSpawner({ 6986, 0 }, "Red", ColMap, { 7357, 900 }, 5); // am
	s1->SetAmbushTrue();
	CreateSpawner({ 7350, 0 }, "blue", ColMap, { 8400, 544 }, 5);
	MonsterSpawner* s2 = CreateSpawner({ 8340, 0 }, "red", ColMap, { 8590, 900 }, 5); // am
	s2->SetAmbushTrue();
	CreateSpawner({ 8590, 0 }, "blue", ColMap, { 9580, 640 }, 5);
	CreateSpawner({ 8640, 0 }, "blue", ColMap, { 9720, 640 }, 5);
	CreateSpawner({ 8690, 0 }, "blue", ColMap, { 9930, 640 }, 5);
	CreateSpawner({ 8740, 0 }, "blue", ColMap, { 10040, 640 }, 5);
	CreateSpawner({ 10110, 0 }, "blue", ColMap, { 11225, 595 }, 5);

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 300, 600 });
	Shantae->GetLevel()->SetCameraPos({ 50, 50 });
}

void Move0::Update(float _DeltaTime)
{
	if (1 == Set)
	{
		Set = 0;

		Player::MainPlayer = SHA;
		Player::MainPlayer->SetPlayerHP(GetPlayLevelHP());
		Player::MainPlayer->SetPlayerMaxHP(GetPlayLevelMaxHP());
		Player::MainPlayer->SetPlayerGem(GetPlayLevelGem());
	}

	OverlapTime += _DeltaTime;

	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Move0_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("HouseFront");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Move1");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}

	if (SHA->GetPos().x >= 11160.0f)
	{
		SHA->CameraMoveFalse();
	}
	else if (SHA->GetPos().x >= 640.0f)
	{
		SHA->CameraMoveTrue();
	}
	else if (SHA->GetPos().x <= 640.0f)
	{
		SHA->CameraMoveFalse();
		Shantae->GetLevel()->SetCameraPos({ 50, 50 });
	}


	if (SHA->GetPos().x >= 11800.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("Move1");
	}

}

void Move0::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	FieldBGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("We_Love_Burning_Town.mp3");
	FieldBGMPlayer.Volume(0.0f); // ���� ��������
	FieldBGMPlayer.LoopCount(100);

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Move0::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	// BGMPlayer.Stop();
}