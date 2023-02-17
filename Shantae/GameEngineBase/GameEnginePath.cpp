#include <Windows.h>
#include <io.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEnginePath.h"

// Path �����ڴ� �������� ��θ� ����
GameEnginePath::GameEnginePath()
	: Path(std::filesystem::current_path())
{
}

GameEnginePath::GameEnginePath(std::filesystem::path _Path)
	: Path(_Path)
{
}

GameEnginePath::GameEnginePath(const std::string& _Path)
	: Path(_Path)
{
}

GameEnginePath::GameEnginePath(const GameEnginePath& _Other)
	: Path(_Other.Path)
{
}

GameEnginePath::GameEnginePath(GameEnginePath&& _Other) noexcept
	: Path(_Other.Path)
{
}

GameEnginePath::~GameEnginePath()
{
}

// filesystem string ��ȯ �� ����
std::string GameEnginePath::GetPathToString() const
{
	return Path.string();
}

// ���� ��� ���ϸ��� string ��ȯ �� ����
std::string GameEnginePath::GetFileName() const
{
	return Path.filename().string();
}

// ���� ���(string_view)�� ���ڿ��� Path�� ����
void GameEnginePath::SetPath(const std::string_view& _Path)
{
	Path = _Path.data();
}

// ���� ������ �̵�
bool GameEnginePath::Move(const std::string_view& _Path)
{
	Path += _Path;

	if (false == IsExists())
	{
		MsgAssert("�������� �ʴ� ��η� �̵��Ϸ��� �߽��ϴ�.");
		return false;
	}

	return true;
}

// ���� ������ �̵�
void GameEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

// GameEngineDirectory�� MoveParentToDirectory �Լ� ���� �� ȣ��
void GameEnginePath::MoveParentToChildPath(const std::string_view& _String)
{
	// ����(_String)�� ã�� �� ���� Ž��
	while (false == IsRoot())
	{
		if (true == IsExistsToPlusString(_String))
		{
			return;
		}
		MoveParent();
	}

	MsgAssert("�̷� ��θ� �ڽ����� ���� �θ�� �������� �ʽ��ϴ�.");
}

// ���� ��ΰ� Root ������� �Ǻ�
bool GameEnginePath::IsRoot()
{
	return Path.root_path() == Path;
}

// ���� ��ΰ� ��ȿ����(�����ϴ���) �Ǻ�
bool GameEnginePath::IsExists()
{
	return 0 == _access(Path.string().c_str(), 0);
}

// ���� ��ΰ� ��ȿ����(�����ϴ���) �Ǻ�
bool GameEnginePath::IsExistsToPlusString(const std::string_view& _String)
{
	std::string Str = GetPathToString() + _String.data();
	return 0 == _access(Str.c_str(), 0);
}