#pragma once

#include <GameEngineCore/GameEngineLevel.h>

// ���� : ������ ȭ��� ���� ���� �޴�
class UILoad : public GameEngineLevel
{
public:
	// constrcuter destructer
	UILoad();
	~UILoad();

	// delete Function
	UILoad(const UILoad& _Other) = delete;
	UILoad(UILoad&& _Other) noexcept = delete;
	UILoad& operator=(const UILoad& _Other) = delete;
	UILoad& operator=(UILoad&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) {}

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}

private:

};

