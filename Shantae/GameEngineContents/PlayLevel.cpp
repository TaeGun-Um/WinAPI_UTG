#include "PlayLevel.h"

#include "MonsterSpawner.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

MonsterSpawner* PlayLevel::CreateSpawner(const float4& _SpawnerPos, const std::string_view& _MonsterType, GameEngineImage* _MonsterColMap, const float4& _MonstorPos, float _Time)
{
	GameEngineActor* Spawner = CreateActor<MonsterSpawner>();
	MonsterSpawner* SPA = dynamic_cast<MonsterSpawner*>(Spawner);
	Spawner->SetPos(_SpawnerPos);
	SPA->SpawnerSetting(_MonsterType, _MonsterColMap, _MonstorPos, _Time);

	return SPA;
}