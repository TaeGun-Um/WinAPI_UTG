#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class WhiteBox : public GameEngineActor
{
public:
	// constrcuter destructer
	WhiteBox();
	~WhiteBox();

	// delete Function
	WhiteBox(const WhiteBox& _Other) = delete;
	WhiteBox(WhiteBox&& _Other) noexcept = delete;
	WhiteBox& operator=(const WhiteBox& _Other) = delete;
	WhiteBox& operator=(WhiteBox&& _Other) noexcept = delete;

	void FadeInStart(unsigned int _doubling, float _waittime);
	void FadeOutStart(unsigned int _doubling, float _waittime);
	void FadeInBoxKill();
	int GetFadeInCount()
	{
		return FadeInCount;
	}
	bool GetIsFadeInOver()
	{
		return FadeInOver;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* BoxRender = nullptr;

	bool IsFadeIn = false;
	bool FadeInOver = false;
	bool IsFadeOut = false;
	bool FadeOutOver = false;

	int FadeInCount = 0;
	int FadeOutCount = 255;
	int Doubling = 0;

	float FadeInTime = 0.0f;
	float FadeOutTime = 0.0f;
	float WaitTime = 0.0f;

	void FadeIn(float _DeltaTime);
	void FadeOut(float _DeltaTime);
	void Kill();

};

