#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

enum OfItemBox
{
	OCT,
	BUB,
	PIKE,
	MILK,
	MEAT,
	CARD,
};

class GameEngineImage;

// Ό³Έν :
class ItemBox : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemBox();
	~ItemBox();

	// delete Function
	ItemBox(const ItemBox& _Other) = delete;
	ItemBox(ItemBox&& _Other) noexcept = delete;
	ItemBox& operator=(const ItemBox& _Other) = delete;
	ItemBox& operator=(ItemBox&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

	void SetItemValue(OfItemBox _Value)
	{
		ItemValue = _Value;
	}

	int GetCreateCount()
	{
		return CreateCount;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void MoveCalculation(float _DeltaTime);
	void CollisionCheck(float _DeltaTime);
	void BoxOpen();
	void CreateItem();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	GameEngineSoundPlayer BGMPlayer;

	OfItemBox ItemValue = OfItemBox::MEAT;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;

	int Open = 1;
	int CreateCount = 1;
	bool IsHit = false;
};

