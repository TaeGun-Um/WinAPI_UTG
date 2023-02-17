#pragma once

#include <string_view>

#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp> // hpp ������ FMOD Ȱ��

// ���� : ���� ���� �ε� Ŭ����
class GameEngineSound
{
public:
	// ���� ����� ���� �Լ�
	static void SoundUpdate();

	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

	// FMOD_OK == �ε� ����
	void SoundLoad(const std::string_view& _Path);

	// ���� ��� �� FMOD::Channel* ����
	FMOD::Channel* Play();

protected:

private:
	FMOD::Sound* FMODSound = nullptr;

};

