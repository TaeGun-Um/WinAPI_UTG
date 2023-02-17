#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : 게임 선택창 배경(1280x720)
class Health : public GameEngineActor
{
public:
	static Health* HealthPtr;

	static Health* GetHealthPtr()
	{
		return HealthPtr;
	}

	// constrcuter destructer
	Health();
	~Health();

	// delete Function
	Health(const Health& _Other) = delete;
	Health(Health&& _Other) noexcept = delete;
	Health& operator=(const Health& _Other) = delete;
	Health& operator=(Health&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineRender* AnimationRender2 = nullptr;
	GameEngineRender* AnimationRender3 = nullptr;

	float OverlapTime = 0.0f;
	int PlayerMaxHP = 0;
	int PlayerHP = 0;

	void CurrentPlayerHP();
	void HealthControl(int _PlayerHP);
	void CreateNewHealth();

	bool NewHealth1 = false;
};

