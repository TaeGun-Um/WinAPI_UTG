#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

// 설명 : 게임 선택창 배경(1280x720)
class GemWindow : public GameEngineActor
{
public:
	static GemWindow* GemWindowPtr;

	static GemWindow* GetGemWindowPtr()
	{
		return GemWindowPtr;
	}

	// constrcuter destructer
	GemWindow();
	~GemWindow();

	// delete Function
	GemWindow(const GemWindow& _Other) = delete;
	GemWindow(GemWindow&& _Other) noexcept = delete;
	GemWindow& operator=(const GemWindow& _Other) = delete;
	GemWindow& operator=(GemWindow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	NumberRenderObject GemNumber;
	float OverlapTime = 0.0f;

	int NumberOfGems = 0;

	void CurrentPlayerGem();
	void GemNumberControl();

};

