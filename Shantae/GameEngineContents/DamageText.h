#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class DamageText : public GameEngineActor
{
public:
	// constrcuter destructer
	DamageText();
	~DamageText();

	// delete Function
	DamageText(const DamageText& _Other) = delete;
	DamageText(DamageText&& _Other) noexcept = delete;
	DamageText& operator=(const DamageText& _Other) = delete;
	DamageText& operator=(DamageText&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Kill();

	GameEngineRender* TextRender = nullptr;

	std::string GetDamage = "- ";
	float KillTime = 0.0f;

};

