#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>

// fmodL = 디버그
// fmod = 릴리즈(?)
#ifdef _DEBUG
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib") // lib를 통해서 dll을 사용한다고 하는건 fmod.dll을 쓰겠다는 뜻
#else
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

// FMOD는 자신들의 기능을 이용할수 있게 해주는 클래스의 포인터를 준다.
FMOD::System* SoundSystem = nullptr;

// 데이터 영역에 생성자를 만들어줘도, GESound가 외부에서 아예 활용되지 못한다면 클래스 자체가 무시되기 떄문에 생성자가 만들어지지 못한다.
// 이럴때는 아무 함수나 만든 뒤 외부에서 한 번만이라도 활용될 수 있도록 해준다.
class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
		FMOD::System_Create(&SoundSystem);

		if (nullptr == SoundSystem)
		{
			MsgAssert("사운드 초기화가 제대로 되지 않았습니다.");
		}

		// 사운드카드 쓸거냐? 안씀(기본)
		if (FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgAssert("사운드 시스템 이니셜라이즈에 실패했습니다.");
		}

	}

	~SoundSystemCreator()
	{
		SoundSystem->release();
	}
};

SoundSystemCreator SoundInitObject = SoundSystemCreator();

 // playSound()를 실시하면 FMOD는 해당 사실(음악 재생)을 알고 있다.
 // 따라서 동시 재생이 가능하다.
 // 동시재생은 SoundUpdate()로 활용 (static)
void GameEngineSound::SoundUpdate()
{
	if (nullptr == SoundSystem)
	{
		MsgAssert("사운드 업데이트가 불가능합니다.");
		return;
	}

	SoundSystem->update();
}

GameEngineSound::GameEngineSound()
{
}

GameEngineSound::~GameEngineSound()
{
}

void GameEngineSound::SoundLoad(const std::string_view& _Path)
{
	// FMOD_LOOP_NORMAL == Loop 횟수를 넣어주면 그 횟수만큼 루프가 가능
	// FMOD_DEFALUT     == 한 번 재생하고 끝
	// 사운드 특이사항   == 없으면 nullptr
	// &FMODSound       == const가 붙지 않은 FMOD::Sound 이중 포인터, 값이 바뀔 수 있다.
	// 하나라도 잘못되면 FMOD_OK가 아니다.
	std::string UTF8Path = GameEngineString::AnsiToUTF8(_Path);

	if (FMOD_OK != SoundSystem->createSound(UTF8Path.c_str(), FMOD_LOOP_NORMAL, nullptr, &FMODSound))
	{
		MsgAssert(std::string("사운드 로드에 실패했습니다.\n 경로 : ") + _Path.data());
	}

	return;
}

// 음악 재생 후 FMOD::Channel* 리턴
FMOD::Channel* GameEngineSound::Play()
{
	if (nullptr == FMODSound)
	{
		MsgAssert(std::string("FMODSound가 nullptr 입니다 "));
	}

	FMOD::Channel* Return;

	// 채널 그룹(충돌 그룹, 랜더링 그룹과 같다고 생각) 안나누면 nullptr
	// 사운드를 멈춘 상태로만들 것인지, 아니라면 false
	// 채널을 어떻게 조절할 것인가 == 속도 조절, 볼륨 조절, 멈추기, 반복 등 >> 값을 리턴하는 형식으로 외부에서 조절하도록함(FMOD::Channel* 값을 리턴)
	SoundSystem->playSound(FMODSound, nullptr, false, &Return);

	return Return; // (FMOD::Channel* 값을 리턴)
}