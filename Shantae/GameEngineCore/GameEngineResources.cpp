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

// 이미지와 사운드 동적할당 해제
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

// 경로와 파일명을 문자열로 변환 후 아래 함수 수행
GameEngineImage* GameEngineResources::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str(), _Path.GetFileName().c_str());
}

// 결정한 이미지에 대한 동적할당 실시 (GameEngineImage 콜)
GameEngineImage* GameEngineResources::ImageLoad(const std::string_view& _Path, const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (AllImage.end() != AllImage.find(UpperName))
	{
		MsgAssert("이미 로드한 이미지를 또 로드하려고 했습니다." + UpperName);
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->ImageLoad(_Path);
	AllImage.insert(std::make_pair(UpperName, NewImage));
	return NewImage;
}

// AllImage map에 저장한 이미지 파일 탐색
GameEngineImage* GameEngineResources::ImageFind(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::map<std::string, GameEngineImage*>::iterator FindIter = AllImage.find(UpperName);

	if (AllImage.end() == FindIter)
	{
		MsgAssert("로드하지 않은 이미지를 사용하려고 했습니다" + UpperName);
		return nullptr;
	}

	return FindIter->second;
}

////////////////////////////////////////////// Sound //////////////////////////////////////////////

// 경로와 파일명을 문자열로 변환 후 아래 함수 수행
GameEngineSound* GameEngineResources::SoundLoad(const GameEnginePath& _Path)
{
	return SoundLoad(_Path.GetPathToString().c_str(), _Path.GetFileName().c_str());
}

// 결정한 사운드에 대한 동적할당 실시 (GameEngineSound 콜)
GameEngineSound* GameEngineResources::SoundLoad(const std::string_view& _Path, const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (AllSound.end() != AllSound.find(UpperName))
	{
		MsgAssert("이미 로드한 이미지를 또 로드하려고 했습니다." + UpperName);
		return nullptr;
	}

	GameEngineSound* NewSound = new GameEngineSound();
	NewSound->SoundLoad(_Path);
	AllSound.insert(std::make_pair(UpperName, NewSound));
	return NewSound;
}

// AllSound map에 저장한 사운드 파일 탐색
GameEngineSound* GameEngineResources::SoundFind(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::map<std::string, GameEngineSound*>::iterator FindIter = AllSound.find(UpperName);

	if (AllSound.end() == FindIter)
	{
		MsgAssert("로드하지 않은 이미지를 사용하려고 했습니다" + UpperName);
		return nullptr;
	}

	return FindIter->second;
}

// 사운드 재생(루프는 0)
void GameEngineResources::SoundPlay(const std::string_view& _Name)
{
	GameEngineSound* Sound = SoundFind(_Name);
	FMOD::Channel* Ch = Sound->Play();
	Ch->setLoopCount(0);
}

// 사운드 재생
GameEngineSoundPlayer GameEngineResources::SoundPlayToControl(const std::string_view& _Name)
{
	GameEngineSound* Sound = SoundFind(_Name);
	return Sound->Play();
}

////////////////////////////////////////////// SoundPlayer //////////////////////////////////////////////

// ControlChannel 이니셜라이져
GameEngineSoundPlayer::GameEngineSoundPlayer(FMOD::Channel* _Channel)
	: ControlChannel(_Channel)
{

}

// 루프 횟수 조절
void GameEngineSoundPlayer::LoopCount(int _Count)
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("재생하지도 않은 사운드를 컨트롤하겠다고 했습니다.");
	}

	ControlChannel->setLoopCount(_Count - 1);
}

// 재생 정지 (다시 틀면 처음부터 재생)
void GameEngineSoundPlayer::Stop()
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("재생하지도 않은 사운드를 컨트롤하겠다고 했습니다.");
	}

	ControlChannel->stop();
}

// 볼륨 조절
void GameEngineSoundPlayer::Volume(float _Volume)
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("재생하지도 않은 사운드를 컨트롤하겠다고 했습니다.");
	}

	ControlChannel->setVolume(_Volume);
}

// 일시 정지
void GameEngineSoundPlayer::PauseOn()
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("재생하지도 않은 사운드를 컨트롤하겠다고 했습니다.");
	}

	ControlChannel->setPaused(true);
}

// 일시 정지 해제
void GameEngineSoundPlayer::PauseOff()
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("재생하지도 않은 사운드를 컨트롤하겠다고 했습니다.");
	}

	ControlChannel->setPaused(false);
}

// 정지중인지 확인
bool GameEngineSoundPlayer::GetPause()
{
	bool PauseValue = false;
	ControlChannel->getPaused(&PauseValue);
	return PauseValue;
}