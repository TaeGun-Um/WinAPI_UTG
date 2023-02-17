#pragma once

#include <filesystem>

// 설명 : 경로에 관련된 기능을 대표하는 클래스, 상대 경로를 문자열로 가지고 있음
class GameEnginePath
{
	friend class GameEngineFile;      // 전방선언과 frined를 동시에 할 수도 있다.
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

	// filesystem string 변환 후 리턴
	std::string GetPathToString() const;

	// 현재 경로 파일명을 string 변환 후 리턴
	std::string GetFileName() const;

	// 현재 경로(string_view)을 문자열로 Path에 저장
	void SetPath(const std::string_view& _Path);

	// 하위 폴더로 이동
	bool Move(const std::string_view& _Path);

	// 상위 폴더로 이동
	void MoveParent();

	// 경로를 탐색하며 _String 폴더가 있는지 확인
	void MoveParentToChildPath(const std::string_view& _String);

	// 현재 경로가 Root 경로인지 판별
	bool IsRoot();

	// 현재 경로가 유요한지 판별
	bool IsExists();

	// 현재 경로가 유효한지 판별
	bool IsExistsToPlusString(const std::string_view& _String);

protected:

private:
	std::filesystem::path Path;

};

