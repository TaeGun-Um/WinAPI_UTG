#pragma once

#include <map>
#include <string>

#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineSound.h>

// Soundplay한 파일에 대해 옵션 조절 (볼륨, 루프, 정지)
class GameEngineSoundPlayer
{
public:
	GameEngineSoundPlayer() {}
	GameEngineSoundPlayer(FMOD::Channel* _Channel); // ControlChannel 이니셜라이져

	void LoopCount(int _Count); // 루프 횟수 조절
	void Volume(float _Volume); // 볼륨 조절
	void Stop();                // 재생 정지 (다시 틀면 처음부터 시작)
	void PauseOn();             // 일시 정지
	void PauseOff();            // 일시 정지 해제

	bool GetPause();            // 일시 정지 상태 확인

private:
	FMOD::Channel* ControlChannel = nullptr;

};

class GameEnginePath;
class GameEngineImage;
class GameEngineSound;

// 설명 : 싱글톤 클래스로 모든 사운드, 이미지(리소스)를 map에 리소스 저장한 뒤 매니지먼트하는 클래스
class GameEngineResources
{
public:
	GameEngineResources(const GameEngineResources& _Other) = delete;
	GameEngineResources(GameEngineResources&& _Other) noexcept = delete;
	GameEngineResources& operator=(const GameEngineResources& _Other) = delete;
	GameEngineResources& operator=(GameEngineResources&& _Other) noexcept = delete;

	// 싱글톤
	static GameEngineResources& GetInst()
	{
		return Inst;
	}

	// 경로와 파일명을 문자열로 변환 후 아래 함수 수행
	GameEngineImage* ImageLoad(const GameEnginePath& _Path);

	// 결정한 이미지에 대한 동적할당 실시 (GameEngineImage 콜)
	GameEngineImage* ImageLoad(const std::string_view& _Path, const std::string_view& _Name);
	
	// AllImage map에 저장한 파일 탐색
	GameEngineImage* ImageFind(const std::string_view& _Name);

	// 이미지 동적할당 해제
	void Release();

	// GameEngineImage를 리소스가 매니지먼트하고 있기 떄문에, GameEngineSound도 동일한 형식으로 작성
	// 경로와 파일명을 문자열로 변환 후 아래 함수 수행
	GameEngineSound* SoundLoad(const GameEnginePath& _Path);

	// 결정한 사운드에 대한 동적할당 실시 (GameEngineImage 콜)
	GameEngineSound* SoundLoad(const std::string_view& _Path, const std::string_view& _Name);

	// AllSound map에 저장한 사운드 파일 탐색
	GameEngineSound* SoundFind(const std::string_view& _Name);

	// Sound에 저장한 파일 탐색 후 재생 (루프 0)
	void SoundPlay(const std::string_view& _Name);

	// Sound에 저장한 파일 탐색 후 재생
	GameEngineSoundPlayer SoundPlayToControl(const std::string_view& _Name);

protected:

private:
	GameEngineResources();
	~GameEngineResources();

	static GameEngineResources Inst;
	
	std::map<std::string, GameEngineImage*> AllImage; // 모든 이미지
	std::map<std::string, GameEngineSound*> AllSound; // 모든 사운드

};

