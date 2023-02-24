#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : House ���� ���
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

