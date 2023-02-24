#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class BlackBox : public GameEngineActor
{
public:
	// constrcuter destructer
	BlackBox();
	~BlackBox();

	// delete Function
	BlackBox(const BlackBox& _Other) = delete;
	BlackBox(BlackBox&& _Other) noexcept = delete;
	BlackBox& operator=(const BlackBox& _Other) = delete;
	BlackBox& operator=(BlackBox&& _Other) noexcept = delete;

	void FadeInStart(unsigned int _doubling, float _waittime);
	void FadeOutStart(unsigned int _doubling, float _waittime);
	void FadeInBoxKill();

	void SetFadeInCount(int _value)
	{
		FadeInCount = 0;
	}

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

