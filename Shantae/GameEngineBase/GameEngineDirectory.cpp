#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineDirectory.h"
#include "GameEngineFile.h"

GameEngineDirectory::GameEngineDirectory()
{
}

GameEngineDirectory::~GameEngineDirectory()
{
}

// 현재 경로에서 하위 폴더(_String)로 이동 (Path 콜)
bool GameEngineDirectory::Move(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;
	return Path.Move(MovePath.c_str());
}

// 현재 경로에서 상위 폴더로 이동 (Path 콜)
bool GameEngineDirectory::MoveParent()
{
	if (true == Path.IsRoot())
	{
		MsgAssert("루트 디렉토리는 부모디렉토리로 이동할수 없습니다.");
		return false;
	}

	Path.MoveParent();

	return true;
}

// 현재 경로에서 이동하며 폴더(_String) 탐색 (Path 콜)
void GameEngineDirectory::MoveParentToDirectory(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;
	Path.MoveParentToChildPath(MovePath.c_str());
}

// 현재 경로에 파일명까지 결합
GameEnginePath GameEngineDirectory::GetPlusFileName(const std::string_view& _String)
{
	std::string PathString = Path.GetPathToString();
	PathString += "\\";
	PathString += _String;
	
	return GameEnginePath(PathString);
}

std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string_view& _Ext)
{
	std::filesystem::directory_iterator DirIter(Path.Path);

	std::string Ext = _Ext.data();

	std::vector<GameEngineFile> Files;

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			// 재귀를 돌리면 다 돌것이다.
			continue;
		}

		Files.push_back(GameEngineFile(Entry.path()));
	}

	return Files;
}