#pragma once

#include <GameEngineCore/GameEngineResources.h>
#include "PlayLevel.h"

class Player;
class TimerCollision;
class Bridge_Boom;
class BoomBridge_Bridge1;
class BoomBridge_Bridge2;
class BoomBridge_Bridge3;
class Soldier_Spider;

// Ό³Έν : FieldLevel_7
class BoomBridge : public PlayLevel
{
public:
	// constrcuter destructer
	BoomBridge();
	~BoomBridge();

	// delete Function
	BoomBridge(const BoomBridge& _Other) = delete;
	BoomBridge(BoomBridge&& _Other) noexcept = delete;
	BoomBridge& operator=(const BoomBridge& _Other) = delete;
	BoomBridge& operator=(BoomBridge&& _Other) noexcept = delete;

protected:
	void Loading();
	void Update(float _DeltaTime);

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	void LevelSet();
	void Debugging();
	void CameraAction();
	void TimerStart();

	GameEngineSoundPlayer BGMPlayer;
	GameEngineActor* Shantae = nullptr;
	GameEngineImage* ColMap = nullptr;

	TimerCollision* TimerCol1 = nullptr;
	TimerCollision* TimerCol2 = nullptr;
	TimerCollision* TimerCol3 = nullptr;
	TimerCollision* TimerCol4 = nullptr;

	Player* SHA = nullptr;
	float OverlapTime = 0.0f;

	bool YCamera = false;
	int Set = 1;
	int AnimationSet = 1;

	// 1
	void Set_One();
	void SetTimerRenewal_One(float _Time);
	BoomBridge_Bridge1* Plat1 = nullptr;
	BoomBridge_Bridge2* Plat2 = nullptr;
	BoomBridge_Bridge3* Plat3 = nullptr;

	Bridge_Boom* Boom1 = nullptr;
	Bridge_Boom* Boom2 = nullptr;

	Soldier_Spider* Soldier1 = nullptr;

	void Set_Two(); // 2
	void SetTimerRenewal_Two(float _Time);
	BoomBridge_Bridge1* Plat4 = nullptr;
	BoomBridge_Bridge2* Plat5 = nullptr;
	BoomBridge_Bridge3* Plat6 = nullptr;

	Bridge_Boom* Boom3 = nullptr;
	Bridge_Boom* Boom4 = nullptr;

	Soldier_Spider* Soldier2 = nullptr;
	Soldier_Spider* Soldier3 = nullptr;

	void Set_Three(); // 3
	void SetTimerRenewal_Three(float _Time);
	BoomBridge_Bridge1* Plat7 = nullptr;
	BoomBridge_Bridge2* Plat8 = nullptr;
	BoomBridge_Bridge3* Plat9 = nullptr;

	Bridge_Boom* Boom5 = nullptr;
	Bridge_Boom* Boom6 = nullptr;

	Soldier_Spider* Soldier4 = nullptr;
	Soldier_Spider* Soldier5 = nullptr;
	Soldier_Spider* Soldier6 = nullptr;

	void Set_Four(); // 4
	void SetTimerRenewal_Four(float _Time);
	BoomBridge_Bridge1* Plat10 = nullptr;
	BoomBridge_Bridge2* Plat11 = nullptr;
	BoomBridge_Bridge3* Plat12 = nullptr;

	Bridge_Boom* Boom7 = nullptr;
	Bridge_Boom* Boom8 = nullptr;

	Soldier_Spider* Soldier7 = nullptr;
	Soldier_Spider* Soldier8 = nullptr;
	Soldier_Spider* Soldier9 = nullptr;
	Soldier_Spider* Soldier10 = nullptr;
};

