#include <Windows.h>
#include <io.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEnginePath.h"

// Path 생성자는 실행파일 경로를 저장
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

// filesystem string 변환 후 리턴
std::string GameEnginePath::GetPathToString() const
{
	return Path.string();
}

// 현재 경로 파일명을 string 변환 후 리턴
std::string GameEnginePath::GetFileName() const
{
	return Path.filename().string();
}

// 현재 경로(string_view)을 문자열로 Path에 저장
void GameEnginePath::SetPath(const std::string_view& _Path)
{
	Path = _Path.data();
}

// 하위 폴더로 이동
bool GameEnginePath::Move(const std::string_view& _Path)
{
	Path += _Path;

	if (false == IsExists())
	{
		MsgAssert("존재하지 않는 경로로 이동하려고 했습니다.");
		return false;
	}

	return true;
}

// 상위 폴더로 이동
void GameEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

// GameEngineDirectory의 MoveParentToDirectory 함수 실행 시 호출
void GameEnginePath::MoveParentToChildPath(const std::string_view& _String)
{
	// 폴더(_String)를 찾을 때 까지 탐색
	while (false == IsRoot())
	{
		if (true == IsExistsToPlusString(_String))
		{
			return;
		}
		MoveParent();
	}

	MsgAssert("이런 경로를 자식으로 가진 부모는 존재하지 않습니다.");
}

// 현재 경로가 Root 경로인지 판별
bool GameEnginePath::IsRoot()
{
	return Path.root_path() == Path;
}

// 현재 경로가 유효한지(존재하는지) 판별
bool GameEnginePath::IsExists()
{
	return 0 == _access(Path.string().c_str(), 0);
}

// 현재 경로가 유효한지(존재하는지) 판별
bool GameEnginePath::IsExistsToPlusString(const std::string_view& _String)
{
	std::string Str = GetPathToString() + _String.data();
	return 0 == _access(Str.c_str(), 0);
}