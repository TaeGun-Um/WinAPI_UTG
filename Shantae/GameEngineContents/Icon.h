#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

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

	int GetItemCount()
	{
		return ItemCount;
	}

	void SetItemCount(int _Value)
	{
		ItemCount = _Value;
	}

	void PlusItemCount()
	{
		ItemCount += 1;
	}

	void MinusItemCount()
	{
		ItemCount -= 1;
	}

	void SetIconName(std::string_view _Name)
	{
		IconName = _Name;
	}

	std::string_view GetIconName()
	{
		return IconName;
	}
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void IconSelect();
	void CreateNumber();
	void CurrentPlayerItemNumber();
	void ItemNumberControl();

	GameEngineRender* AnimationRender = nullptr;
	std::string IconName = "Milk";
	NumberRenderObject ItemNumber;

	int NumberCreate = 1;
	int ItemCount = 1;

	bool IsNumberCreate = false;
};

