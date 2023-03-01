#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Icon : public GameEngineActor
{
public:
	// constrcuter destructer
	Icon();
	~Icon();

	// delete Function
	Icon(const Icon& _Other) = delete;
	Icon(Icon&& _Other) noexcept = delete;
	Icon& operator=(const Icon& _Other) = delete;
	Icon& operator=(Icon&& _Other) noexcept = delete;

	void SetCount(int _Value)
	{
		Count = _Value;
	}

	void SetIconName(std::string_view _Name)
	{
		IconName = _Name;
	}
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void IconSelect();

	GameEngineRender* AnimationRender = nullptr;
	std::string IconName = "Milk";
	int Count = 0;
};

