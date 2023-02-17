#pragma once

#include <GameEngineCore/GameEngineLevel.h>

#include "MonsterSpawner.h"

class Player;

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

	MonsterSpawner* CreateSpawner(const float4& _SpawnerPos, const std::string_view& _MonsterType, GameEngineImage* _MonsterColMap, const float4& _MonstorPos, float _Time);

private:
	int PlayLevelHP = 8;
	int PlayLevelMaxHP = 8;
	int PlayLevelGem = 0;
};