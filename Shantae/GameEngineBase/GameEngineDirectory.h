#pragma once

#include <vector>
#include <string_view>
#include "GameEnginePath.h"

class GameEngineFile;

// 설명 : Path를 활용하여 Directory을 수정하는 클래스
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

	// 현재 경로에서 하위 폴더로 이동
	bool Move(const std::string_view& _String);

	// 현재 경로에서 상위 폴더로 이동
	bool MoveParent();

	// 현재 경로에서 이동하며 폴더(_String) 탐색 (Path 콜)
	void MoveParentToDirectory(const std::string_view& _String);

	// 현재 경로에 파일명까지 결합
	GameEnginePath GetPlusFileName(const std::string_view& _String);

	// 하위는 돌지 않고 그 디렉토리에 해당하는 모든 파일만 리턴해주는 함수.
	std::vector<GameEngineFile> GetAllFile(const std::string_view& _Ext = "");

protected:

private:
	// 현재 경로를 저장한 자료형
	GameEnginePath Path;
};

