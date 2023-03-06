#pragma once

#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class Soldier_Blue;
class Soldier_Black;
class Soldier_Red;
class Soldier_Bomberman;
class Soldier_Spider;

// Ό³Έν : Player Chracter
class MonsterSpawner : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterSpawner();
	~MonsterSpawner();

	// delete Function
	MonsterSpawner(const MonsterSpawner& _Other) = delete;
	MonsterSpawner(MonsterSpawner&& _Other) noexcept = delete;
	MonsterSpawner& operator=(const MonsterSpawner& _Other) = delete;
	MonsterSpawner& operator=(MonsterSpawner&& _Other) noexcept = delete;

	void SetAmbushTrue()
	{
		IsAmbush = true;
	}

	void SpawnerSetting(const std::string_view& _Type, GameEngineImage* _ColMap, const float4 _Value, float _Time);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) {}

private:
	GameEngineCollision* SpawnSpot = nullptr;
	GameEngineRender* TextRender1 = nullptr;
	GameEngineRender* TextRender2 = nullptr;
	GameEngineRender* TextRender3 = nullptr;

	int Spawncount = 0;
	float SpawnTime = 0.0f;
	float AccTime = 0.0f;

	Soldier_Blue* BlueM = nullptr;
	Soldier_Red* RedM = nullptr;
	Soldier_Black* BlackM = nullptr;
	Soldier_Bomberman* BombermanM = nullptr;
	Soldier_Spider* SpiderM = nullptr;

	bool IsBlue = false;
	bool IsBomberman = false;
	bool IsRed = false;
	bool IsBlack = false;
	bool IsSpider = false;

	bool IsAmbush = false;

	bool IsText = false;

	GameEngineImage* MonsterColMap = nullptr;
	std::vector<std::string> SpawnerText;
	std::string MonsterTYPE = "Blue";
	float4 MonsterPos = float4::Zero;
	float4 BoxScale = { 50, 50 };

	void CollisionCheck();

	void BlueSpawn();
	void RedSpawn();
	void BlackSpawn();
	void SpiderSpawn();
	void BombermanSpawn();
	void PositionText();

};

