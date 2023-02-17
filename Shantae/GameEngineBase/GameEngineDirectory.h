#pragma once

#include <vector>
#include <string_view>
#include "GameEnginePath.h"

class GameEngineFile;

// ���� : Path�� Ȱ���Ͽ� Directory�� �����ϴ� Ŭ����
class GameEngineDirectory
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	~GameEngineDirectory();

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	// ���� ��ο��� ���� ������ �̵�
	bool Move(const std::string_view& _String);

	// ���� ��ο��� ���� ������ �̵�
	bool MoveParent();

	// ���� ��ο��� �̵��ϸ� ����(_String) Ž�� (Path ��)
	void MoveParentToDirectory(const std::string_view& _String);

	// ���� ��ο� ���ϸ���� ����
	GameEnginePath GetPlusFileName(const std::string_view& _String);

	// ������ ���� �ʰ� �� ���丮�� �ش��ϴ� ��� ���ϸ� �������ִ� �Լ�.
	std::vector<GameEngineFile> GetAllFile(const std::string_view& _Ext = "");

protected:

private:
	// ���� ��θ� ������ �ڷ���
	GameEnginePath Path;
};

