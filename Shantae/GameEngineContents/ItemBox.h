#pragma once

#include <GameEngineCore/GameEngineActor.h>

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

};

