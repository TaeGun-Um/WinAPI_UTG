#pragma once

#include <GameEngineCore/GameEngineLevel.h>

#include "MonsterSpawner.h"

class Player;
class Inventory;

// Ό³Έν : Scuttle Town ~ outskirts
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	void Loading() {}
	void Update(float _DeltaTime) {}

	void LevelChangeEnd(GameEngineLevel* _NextLevel) {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) {}

	int GetPlayLevelHP()
	{
		return PlayLevelHP;
	}

	void SetPlayLevelHP(int _Value)
	{
		PlayLevelHP = _Value;
	}

	int GetPlayLevelMaxHP()
	{
		return PlayLevelMaxHP;
	}

	void SetPlayLevelMaxHP(int _Value)
	{
		PlayLevelMaxHP = _Value;
	}

	int GetPlayLevelGem()
	{
		return PlayLevelGem;
	}

	void SetPlayLevelGem(int _Value)
	{
		PlayLevelGem = _Value;
	}

	int GetPlayLevelMonsterMilk()
	{
		return MonsterMilk;
	}

	void SetPlayLevelMonsterMilk(int _Value)
	{
		MonsterMilk = _Value;
	}

	int GetPlayLevelPikeBall()
	{
		return PikeBall;
	}

	void SetPlayLevelPikeBall(int _Value)
	{
		PikeBall = _Value;
	}

	int GetPlayLevelBubble()
	{
		return Bubble;
	}

	void SetPlayLevelBubble(int _Value)
	{
		Bubble = _Value;
	}

	int GetPlayLevelOctopus()
	{
		return Octopus;
	}

	void SetPlayLevelOctopus(int _Value)
	{
		Octopus = _Value;
	}

	int GetPlayLevelMeat()
	{
		return Meat;
	}

	void SetPlayLevelMeat(int _Value)
	{
		Meat = _Value;
	}

	int GetPlayLevelIDCard()
	{
		return IDCard;
	}

	void SetPlayLevelIDCard(int _Value)
	{
		IDCard = _Value;
	}

	MonsterSpawner* CreateSpawner(const float4& _SpawnerPos, const std::string_view& _MonsterType, GameEngineImage* _MonsterColMap, const float4& _MonstorPos, float _Time);

private:
	int PlayLevelHP = 8;
	int PlayLevelMaxHP = 8;
	int PlayLevelGem = 0;

	int MonsterMilk = 0;
	int PikeBall = 0;
	int Bubble = 0;
	int Octopus = 0;
	int Meat = 0;
	int IDCard = 0;
};