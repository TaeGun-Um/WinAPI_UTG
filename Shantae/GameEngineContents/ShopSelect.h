#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ShopSelect : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopSelect();
	~ShopSelect();

	// delete Function
	ShopSelect(const ShopSelect& _Other) = delete;
	ShopSelect(ShopSelect&& _Other) noexcept = delete;
	ShopSelect& operator=(const ShopSelect& _Other) = delete;
	ShopSelect& operator=(ShopSelect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

