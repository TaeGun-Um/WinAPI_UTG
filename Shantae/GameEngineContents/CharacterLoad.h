#pragma once

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineLevel.h>

class GameEngineDirectory;

// 설명 : 오프닝 화면과 게임 시작 메뉴
class CharacterLoad : public GameEngineLevel
{
public:
	// constrcuter destructer
	CharacterLoad();
	~CharacterLoad();

	// delete Function
	CharacterLoad(const CharacterLoad& _Other) = delete;
	CharacterLoad(CharacterLoad&& _Other) noexcept = delete;
	CharacterLoad& operator=(const CharacterLoad& _Other) = delete;
	CharacterLoad& operator=(CharacterLoad&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) {}

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}

private:
	GameEngineDirectory Dir;

};

