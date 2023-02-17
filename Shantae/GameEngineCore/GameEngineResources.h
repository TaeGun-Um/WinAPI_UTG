#pragma once

#include <map>
#include <string>

#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineSound.h>

// Soundplay�� ���Ͽ� ���� �ɼ� ���� (����, ����, ����)
class GameEngineSoundPlayer
{
public:
	GameEngineSoundPlayer() {}
	GameEngineSoundPlayer(FMOD::Channel* _Channel); // ControlChannel �̴ϼȶ�����

	void LoopCount(int _Count); // ���� Ƚ�� ����
	void Volume(float _Volume); // ���� ����
	void Stop();                // ��� ���� (�ٽ� Ʋ�� ó������ ����)
	void PauseOn();             // �Ͻ� ����
	void PauseOff();            // �Ͻ� ���� ����

	bool GetPause();            // �Ͻ� ���� ���� Ȯ��

private:
	FMOD::Channel* ControlChannel = nullptr;

};

class GameEnginePath;
class GameEngineImage;
class GameEngineSound;

// ���� : �̱��� Ŭ������ ��� ����, �̹���(���ҽ�)�� map�� ���ҽ� ������ �� �Ŵ�����Ʈ�ϴ� Ŭ����
class GameEngineResources
{
public:
	GameEngineResources(const GameEngineResources& _Other) = delete;
	GameEngineResources(GameEngineResources&& _Other) noexcept = delete;
	GameEngineResources& operator=(const GameEngineResources& _Other) = delete;
	GameEngineResources& operator=(GameEngineResources&& _Other) noexcept = delete;

	// �̱���
	static GameEngineResources& GetInst()
	{
		return Inst;
	}

	// ��ο� ���ϸ��� ���ڿ��� ��ȯ �� �Ʒ� �Լ� ����
	GameEngineImage* ImageLoad(const GameEnginePath& _Path);

	// ������ �̹����� ���� �����Ҵ� �ǽ� (GameEngineImage ��)
	GameEngineImage* ImageLoad(const std::string_view& _Path, const std::string_view& _Name);
	
	// AllImage map�� ������ ���� Ž��
	GameEngineImage* ImageFind(const std::string_view& _Name);

	// �̹��� �����Ҵ� ����
	void Release();

	// GameEngineImage�� ���ҽ��� �Ŵ�����Ʈ�ϰ� �ֱ� ������, GameEngineSound�� ������ �������� �ۼ�
	// ��ο� ���ϸ��� ���ڿ��� ��ȯ �� �Ʒ� �Լ� ����
	GameEngineSound* SoundLoad(const GameEnginePath& _Path);

	// ������ ���忡 ���� �����Ҵ� �ǽ� (GameEngineImage ��)
	GameEngineSound* SoundLoad(const std::string_view& _Path, const std::string_view& _Name);

	// AllSound map�� ������ ���� ���� Ž��
	GameEngineSound* SoundFind(const std::string_view& _Name);

	// Sound�� ������ ���� Ž�� �� ��� (���� 0)
	void SoundPlay(const std::string_view& _Name);

	// Sound�� ������ ���� Ž�� �� ���
	GameEngineSoundPlayer SoundPlayToControl(const std::string_view& _Name);

protected:

private:
	GameEngineResources();
	~GameEngineResources();

	static GameEngineResources Inst;
	
	std::map<std::string, GameEngineImage*> AllImage; // ��� �̹���
	std::map<std::string, GameEngineSound*> AllSound; // ��� ����

};

