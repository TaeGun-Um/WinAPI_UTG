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

	void SetOctopusHeart()
	{
		OctopusHeart = true;
	}

	void SetNewCreate()
	{
		NewCreate = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	GameEngineRender* Heart1 = nullptr;
	GameEngineRender* Heart2 = nullptr;
	GameEngineRender* Heart3 = nullptr;
	GameEngineRender* Heart4 = nullptr;
	GameEngineRender* Heart5 = nullptr;

	float OverlapTime = 0.0f;
	int NewMaxHP = 0;
	int PlayerMaxHP = 0;
	int PlayerHP = 0;

	void CurrentPlayerHP();
	void HealthControl(int _PlayerHP);
	void CreateNewHealth();

	bool OctopusHeart = false;
	bool NewCreate = false;
};

