#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HeartText : public GameEngineActor
{
public:
	// constrcuter destructer
	HeartText();
	~HeartText();

	// delete Function
	HeartText(const HeartText& _Other) = delete;
	HeartText(HeartText&& _Other) noexcept = delete;
	HeartText& operator=(const HeartText& _Other) = delete;
	HeartText& operator=(HeartText&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Kill();

	GameEngineRender* TextRender = nullptr;

	std::string GetDamage = "- ";
	float KillTime = 0.0f;

};

