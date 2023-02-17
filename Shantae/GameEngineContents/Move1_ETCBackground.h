#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : Move1_Map �ڿ� ��ġ�Ǵ� ������Ʈ��
class Move1_ETCBackground : public GameEngineActor
{
public:
	// constrcuter destructer
	Move1_ETCBackground();
	~Move1_ETCBackground();

	// delete Function
	Move1_ETCBackground(const Move1_ETCBackground& _Other) = delete;
	Move1_ETCBackground(Move1_ETCBackground&& _Other) noexcept = delete;
	Move1_ETCBackground& operator=(const Move1_ETCBackground& _Other) = delete;
	Move1_ETCBackground& operator=(Move1_ETCBackground&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

