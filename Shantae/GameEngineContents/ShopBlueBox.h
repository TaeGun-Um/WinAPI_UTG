#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ShopBlueBox : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopBlueBox();
	~ShopBlueBox();

	// delete Function
	ShopBlueBox(const ShopBlueBox& _Other) = delete;
	ShopBlueBox(ShopBlueBox&& _Other) noexcept = delete;
	ShopBlueBox& operator=(const ShopBlueBox& _Other) = delete;
	ShopBlueBox& operator=(ShopBlueBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

