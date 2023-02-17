#pragma once

#include <filesystem>

// ���� : ��ο� ���õ� ����� ��ǥ�ϴ� Ŭ����, ��� ��θ� ���ڿ��� ������ ����
class GameEnginePath
{
	friend class GameEngineFile;      // ���漱��� frined�� ���ÿ� �� ���� �ִ�.
	friend class GameEngineDirectory;

public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(std::filesystem::path _Path);
	GameEnginePath(const std::string& _Path);
	
	~GameEnginePath();

	// delete Function
	GameEnginePath(const GameEnginePath& _Other);
	GameEnginePath(GameEnginePath&& _Other) noexcept;
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	// filesystem string ��ȯ �� ����
	std::string GetPathToString() const;

	// ���� ��� ���ϸ��� string ��ȯ �� ����
	std::string GetFileName() const;

	// ���� ���(string_view)�� ���ڿ��� Path�� ����
	void SetPath(const std::string_view& _Path);

	// ���� ������ �̵�
	bool Move(const std::string_view& _Path);

	// ���� ������ �̵�
	void MoveParent();

	// ��θ� Ž���ϸ� _String ������ �ִ��� Ȯ��
	void MoveParentToChildPath(const std::string_view& _String);

	// ���� ��ΰ� Root ������� �Ǻ�
	bool IsRoot();

	// ���� ��ΰ� �������� �Ǻ�
	bool IsExists();

	// ���� ��ΰ� ��ȿ���� �Ǻ�
	bool IsExistsToPlusString(const std::string_view& _String);

protected:

private:
	std::filesystem::path Path;

};

