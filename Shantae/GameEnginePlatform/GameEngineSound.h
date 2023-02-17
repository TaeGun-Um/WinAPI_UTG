#pragma once

#include <string_view>

#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp> // hpp 형식의 FMOD 활용

// 설명 : 사운드 관련 로드 클래스
class GameEngineSound
{
public:
	// 동시 재생을 위한 함수
	static void SoundUpdate();

	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

	// FMOD_OK == 로드 성공
	void SoundLoad(const std::string_view& _Path);

	// 음악 재생 후 FMOD::Channel* 리턴
	FMOD::Channel* Play();

protected:

private:
	FMOD::Sound* FMODSound = nullptr;

};

