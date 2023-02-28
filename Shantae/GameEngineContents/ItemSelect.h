#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class ItemSelect : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemSelect();
	~ItemSelect();

	// delete Function
	ItemSelect(const ItemSelect& _Other) = delete;
	ItemSelect(ItemSelect&& _Other) noexcept = delete;
	ItemSelect& operator=(const ItemSelect& _Other) = delete;
	ItemSelect& operator=(ItemSelect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

	GameEngineSoundPlayer BGMPlayer;

};

