#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BlueTextBox : public GameEngineActor
{
public:
	static BlueTextBox* DialogTextBox;

	// constrcuter destructer
	BlueTextBox();
	~BlueTextBox();

	// delete Function
	BlueTextBox(const BlueTextBox& _Other) = delete;
	BlueTextBox(BlueTextBox&& _Other) noexcept = delete;
	BlueTextBox& operator=(const BlueTextBox& _Other) = delete;
	BlueTextBox& operator=(BlueTextBox&& _Other) noexcept = delete;

	GameEngineRender* AnimationRender = nullptr;

	void SetIsOpen()
	{
		IsOpen = true;
	}

	void Open();
	void Close();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void TextCreate();
	void Kill();

	GameEngineSoundPlayer BGMPlayer;
	
	bool IsOpen = false;
	bool IsClose = false;

	int TextCount = 1;

};

