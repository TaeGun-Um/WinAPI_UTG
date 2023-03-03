#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>

class NPCScript;

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Open();
	void Close(float _DeltaTime);
	void TextCreate();
	void Kill();

	GameEngineSoundPlayer BGMPlayer;
	
	NPCScript* Scr = nullptr;

	bool IsOpen = false;
	bool IsClose = false;

	float OpenTime = 0.0f;
	float CloseTime = 0.0f;
	int TextCount = 1;

};

