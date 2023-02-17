#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>

// fmodL = �����
// fmod = ������(?)
#ifdef _DEBUG
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib") // lib�� ���ؼ� dll�� ����Ѵٰ� �ϴ°� fmod.dll�� ���ڴٴ� ��
#else
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

// FMOD�� �ڽŵ��� ����� �̿��Ҽ� �ְ� ���ִ� Ŭ������ �����͸� �ش�.
FMOD::System* SoundSystem = nullptr;

// ������ ������ �����ڸ� ������൵, GESound�� �ܺο��� �ƿ� Ȱ����� ���Ѵٸ� Ŭ���� ��ü�� ���õǱ� ������ �����ڰ� ��������� ���Ѵ�.
// �̷����� �ƹ� �Լ��� ���� �� �ܺο��� �� �����̶� Ȱ��� �� �ֵ��� ���ش�.
class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
		FMOD::System_Create(&SoundSystem);

		if (nullptr == SoundSystem)
		{
			MsgAssert("���� �ʱ�ȭ�� ����� ���� �ʾҽ��ϴ�.");
		}

		// ����ī�� ���ų�? �Ⱦ�(�⺻)
		if (FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgAssert("���� �ý��� �̴ϼȶ���� �����߽��ϴ�.");
		}

	}

	~SoundSystemCreator()
	{
		SoundSystem->release();
	}
};

SoundSystemCreator SoundInitObject = SoundSystemCreator();

 // playSound()�� �ǽ��ϸ� FMOD�� �ش� ���(���� ���)�� �˰� �ִ�.
 // ���� ���� ����� �����ϴ�.
 // ��������� SoundUpdate()�� Ȱ�� (static)
void GameEngineSound::SoundUpdate()
{
	if (nullptr == SoundSystem)
	{
		MsgAssert("���� ������Ʈ�� �Ұ����մϴ�.");
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
	// FMOD_LOOP_NORMAL == Loop Ƚ���� �־��ָ� �� Ƚ����ŭ ������ ����
	// FMOD_DEFALUT     == �� �� ����ϰ� ��
	// ���� Ư�̻���   == ������ nullptr
	// &FMODSound       == const�� ���� ���� FMOD::Sound ���� ������, ���� �ٲ� �� �ִ�.
	// �ϳ��� �߸��Ǹ� FMOD_OK�� �ƴϴ�.
	std::string UTF8Path = GameEngineString::AnsiToUTF8(_Path);

	if (FMOD_OK != SoundSystem->createSound(UTF8Path.c_str(), FMOD_LOOP_NORMAL, nullptr, &FMODSound))
	{
		MsgAssert(std::string("���� �ε忡 �����߽��ϴ�.\n ��� : ") + _Path.data());
	}

	return;
}

// ���� ��� �� FMOD::Channel* ����
FMOD::Channel* GameEngineSound::Play()
{
	if (nullptr == FMODSound)
	{
		MsgAssert(std::string("FMODSound�� nullptr �Դϴ� "));
	}

	FMOD::Channel* Return;

	// ä�� �׷�(�浹 �׷�, ������ �׷�� ���ٰ� ����) �ȳ����� nullptr
	// ���带 ���� ���·θ��� ������, �ƴ϶�� false
	// ä���� ��� ������ ���ΰ� == �ӵ� ����, ���� ����, ���߱�, �ݺ� �� >> ���� �����ϴ� �������� �ܺο��� �����ϵ�����(FMOD::Channel* ���� ����)
	SoundSystem->playSound(FMODSound, nullptr, false, &Return);

	return Return; // (FMOD::Channel* ���� ����)
}