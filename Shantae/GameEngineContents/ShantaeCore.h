#pragma once
#include <GameEngineCore/GameEngineCore.h>

// ���� : �̱��� Ŭ����, GameEngineCore�� ��ӹ޴� �ڽ� Ŭ����
class ShantaeCore : public GameEngineCore
{
public:
	// delete Function
	ShantaeCore(const ShantaeCore& _Other) = delete;
	ShantaeCore(ShantaeCore&& _Other) noexcept = delete;
	ShantaeCore& operator=(const ShantaeCore& _Other) = delete;
	ShantaeCore& operator=(ShantaeCore&& _Other) noexcept = delete;

	// �̱���
	static ShantaeCore& GetInst()
	{
		return Core;
	}

protected:
	// GameEngineCore ���� �����Լ� ovrride
	void Start() override;
	void Update() override;
	void End() override;

private:
	ShantaeCore();
	~ShantaeCore();

	static ShantaeCore Core;

};
