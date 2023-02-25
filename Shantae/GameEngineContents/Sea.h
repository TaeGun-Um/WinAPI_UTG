#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : Move0의 바다
class Sea : public GameEngineActor
{
public:
	// constrcuter destructer
	Sea();
	~Sea();

	// delete Function
	Sea(const Sea& _Other) = delete;
	Sea(Sea&& _Other) noexcept = delete;
	Sea& operator=(const Sea& _Other) = delete;
	Sea& operator=(Sea&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

