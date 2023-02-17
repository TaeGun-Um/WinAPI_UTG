#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>
#include "GameEngineResources.h"

GameEngineResources GameEngineResources::Inst;

GameEngineResources::GameEngineResources()
{
}

GameEngineResources::~GameEngineResources()
{
}

// �̹����� ���� �����Ҵ� ����
void GameEngineResources::Release()
{
	for (std::pair<std::string, GameEngineImage*> Pair : AllImage)
	{
		if (nullptr == Pair.second)
		{
			continue;
		}
		delete Pair.second;
	}
	AllImage.clear();

	for (std::pair<std::string, GameEngineSound*> Pair : AllSound)
	{
		if (nullptr == Pair.second)
		{
			continue;
		}
		delete Pair.second;
	}
	AllSound.clear();
}

////////////////////////////////////////////// Image //////////////////////////////////////////////

// ��ο� ���ϸ��� ���ڿ��� ��ȯ �� �Ʒ� �Լ� ����
GameEngineImage* GameEngineResources::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str(), _Path.GetFileName().c_str());
}

// ������ �̹����� ���� �����Ҵ� �ǽ� (GameEngineImage ��)
GameEngineImage* GameEngineResources::ImageLoad(const std::string_view& _Path, const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (AllImage.end() != AllImage.find(UpperName))
	{
		MsgAssert("�̹� �ε��� �̹����� �� �ε��Ϸ��� �߽��ϴ�." + UpperName);
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->ImageLoad(_Path);
	AllImage.insert(std::make_pair(UpperName, NewImage));
	return NewImage;
}

// AllImage map�� ������ �̹��� ���� Ž��
GameEngineImage* GameEngineResources::ImageFind(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::map<std::string, GameEngineImage*>::iterator FindIter = AllImage.find(UpperName);

	if (AllImage.end() == FindIter)
	{
		MsgAssert("�ε����� ���� �̹����� ����Ϸ��� �߽��ϴ�" + UpperName);
		return nullptr;
	}

	return FindIter->second;
}

////////////////////////////////////////////// Sound //////////////////////////////////////////////

// ��ο� ���ϸ��� ���ڿ��� ��ȯ �� �Ʒ� �Լ� ����
GameEngineSound* GameEngineResources::SoundLoad(const GameEnginePath& _Path)
{
	return SoundLoad(_Path.GetPathToString().c_str(), _Path.GetFileName().c_str());
}

// ������ ���忡 ���� �����Ҵ� �ǽ� (GameEngineSound ��)
GameEngineSound* GameEngineResources::SoundLoad(const std::string_view& _Path, const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (AllSound.end() != AllSound.find(UpperName))
	{
		MsgAssert("�̹� �ε��� �̹����� �� �ε��Ϸ��� �߽��ϴ�." + UpperName);
		return nullptr;
	}

	GameEngineSound* NewSound = new GameEngineSound();
	NewSound->SoundLoad(_Path);
	AllSound.insert(std::make_pair(UpperName, NewSound));
	return NewSound;
}

// AllSound map�� ������ ���� ���� Ž��
GameEngineSound* GameEngineResources::SoundFind(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::map<std::string, GameEngineSound*>::iterator FindIter = AllSound.find(UpperName);

	if (AllSound.end() == FindIter)
	{
		MsgAssert("�ε����� ���� �̹����� ����Ϸ��� �߽��ϴ�" + UpperName);
		return nullptr;
	}

	return FindIter->second;
}

// ���� ���(������ 0)
void GameEngineResources::SoundPlay(const std::string_view& _Name)
{
	GameEngineSound* Sound = SoundFind(_Name);
	FMOD::Channel* Ch = Sound->Play();
	Ch->setLoopCount(0);
}

// ���� ���
GameEngineSoundPlayer GameEngineResources::SoundPlayToControl(const std::string_view& _Name)
{
	GameEngineSound* Sound = SoundFind(_Name);
	return Sound->Play();
}

////////////////////////////////////////////// SoundPlayer //////////////////////////////////////////////

// ControlChannel �̴ϼȶ�����
GameEngineSoundPlayer::GameEngineSoundPlayer(FMOD::Channel* _Channel)
	: ControlChannel(_Channel)
{

}

// ���� Ƚ�� ����
void GameEngineSoundPlayer::LoopCount(int _Count)
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("��������� ���� ���带 ��Ʈ���ϰڴٰ� �߽��ϴ�.");
	}

	ControlChannel->setLoopCount(_Count - 1);
}

// ��� ���� (�ٽ� Ʋ�� ó������ ���)
void GameEngineSoundPlayer::Stop()
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("��������� ���� ���带 ��Ʈ���ϰڴٰ� �߽��ϴ�.");
	}

	ControlChannel->stop();
}

// ���� ����
void GameEngineSoundPlayer::Volume(float _Volume)
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("��������� ���� ���带 ��Ʈ���ϰڴٰ� �߽��ϴ�.");
	}

	ControlChannel->setVolume(_Volume);
}

// �Ͻ� ����
void GameEngineSoundPlayer::PauseOn()
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("��������� ���� ���带 ��Ʈ���ϰڴٰ� �߽��ϴ�.");
	}

	ControlChannel->setPaused(true);
}

// �Ͻ� ���� ����
void GameEngineSoundPlayer::PauseOff()
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("��������� ���� ���带 ��Ʈ���ϰڴٰ� �߽��ϴ�.");
	}

	ControlChannel->setPaused(false);
}

// ���������� Ȯ��
bool GameEngineSoundPlayer::GetPause()
{
	bool PauseValue = false;
	ControlChannel->getPaused(&PauseValue);
	return PauseValue;
}