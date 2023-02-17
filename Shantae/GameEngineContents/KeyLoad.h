#pragma once

#include <GameEngineCore/GameEngineLevel.h>

// ���� : ������ ȭ��� ���� ���� �޴�
class KeyLoad : public GameEngineLevel
{
public:
	// constrcuter destructer
	KeyLoad();
	~KeyLoad();

	// delete Function
	KeyLoad(const KeyLoad& _Other) = delete;
	KeyLoad(KeyLoad&& _Other) noexcept = delete;
	KeyLoad& operator=(const KeyLoad& _Other) = delete;
	KeyLoad& operator=(KeyLoad&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) {}

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}

private:

};

