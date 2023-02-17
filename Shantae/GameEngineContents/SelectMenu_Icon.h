#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : ��ư ���� ������
class SelectMenu_Icon : public GameEngineActor
{
public:
	// constrcuter destructer
	SelectMenu_Icon();
	~SelectMenu_Icon();

	// delete Function
	SelectMenu_Icon(const SelectMenu_Icon& _Other) = delete;
	SelectMenu_Icon(SelectMenu_Icon&& _Other) noexcept = delete;
	SelectMenu_Icon& operator=(const SelectMenu_Icon& _Other) = delete;
	SelectMenu_Icon& operator=(SelectMenu_Icon&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float OverlapTime = 0.0f;
	float DelayTime = 0.2f;
};

