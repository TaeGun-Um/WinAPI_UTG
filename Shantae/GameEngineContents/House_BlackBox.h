#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : House 내부 배경
class House_BlackBox : public GameEngineActor
{
public:
	// constrcuter destructer
	House_BlackBox();
	~House_BlackBox();

	// delete Function
	House_BlackBox(const House_BlackBox& _Other) = delete;
	House_BlackBox(House_BlackBox&& _Other) noexcept = delete;
	House_BlackBox& operator=(const House_BlackBox& _Other) = delete;
	House_BlackBox& operator=(House_BlackBox&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

