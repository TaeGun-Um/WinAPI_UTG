#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : Move0�� �ٴ�
class Move0_Sea : public GameEngineActor
{
public:
	// constrcuter destructer
	Move0_Sea();
	~Move0_Sea();

	// delete Function
	Move0_Sea(const Move0_Sea& _Other) = delete;
	Move0_Sea(Move0_Sea&& _Other) noexcept = delete;
	Move0_Sea& operator=(const Move0_Sea& _Other) = delete;
	Move0_Sea& operator=(Move0_Sea&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

