#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : 오프닝 배경(1280x720)
class Opening_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	Opening_Background();
	~Opening_Background();

	// delete Function
	Opening_Background(const Opening_Background& _Other) = delete;
	Opening_Background(Opening_Background&& _Other) noexcept = delete;
	Opening_Background& operator=(const Opening_Background& _Other) = delete;
	Opening_Background& operator=(Opening_Background&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

