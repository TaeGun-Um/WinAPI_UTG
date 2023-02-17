#pragma once

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineLevel.h>

class GameEngineDirectory;

// ���� : ������ ȭ��� ���� ���� �޴�
class SoundLoad : public GameEngineLevel
{
public:
	// constrcuter destructer
	SoundLoad();
	~SoundLoad();

	// delete Function
	SoundLoad(const SoundLoad& _Other) = delete;
	SoundLoad(SoundLoad&& _Other) noexcept = delete;
	SoundLoad& operator=(const SoundLoad& _Other) = delete;
	SoundLoad& operator=(SoundLoad&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}

private:
	GameEngineDirectory Dir;

};

