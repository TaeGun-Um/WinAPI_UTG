#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : Move0_Map �ڿ� ��ġ�Ǵ� ������Ʈ��
class Move0_ETCBackground : public GameEngineActor
{
public:
	// constrcuter destructer
	Move0_ETCBackground();
	~Move0_ETCBackground();

	// delete Function
	Move0_ETCBackground(const Move0_ETCBackground& _Other) = delete;
	Move0_ETCBackground(Move0_ETCBackground&& _Other) noexcept = delete;
	Move0_ETCBackground& operator=(const Move0_ETCBackground& _Other) = delete;
	Move0_ETCBackground& operator=(Move0_ETCBackground&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

