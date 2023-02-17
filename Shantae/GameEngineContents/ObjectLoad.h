#pragma once

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineLevel.h>

class GameEngineImage;

// 설명 : 오프닝 화면과 게임 시작 메뉴
class ObjectLoad : public GameEngineLevel
{
public:
	static ObjectLoad* ObjectLoadPtr;

	static ObjectLoad* GetObjectLoadPtr()
	{
		return ObjectLoadPtr;
	}

	// constrcuter destructer
	ObjectLoad();
	~ObjectLoad();

	// delete Function
	ObjectLoad(const ObjectLoad& _Other) = delete;
	ObjectLoad(ObjectLoad&& _Other) noexcept = delete;
	ObjectLoad& operator=(const ObjectLoad& _Other) = delete;
	ObjectLoad& operator=(ObjectLoad&& _Other) noexcept = delete;

	GameEngineImage* GetColMap(const std::string_view& _Name);

protected:
	void Loading() override;
	void Update(float _DeltaTime) {}

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}

private:
	GameEngineDirectory Dir;

	void ColMapLoad();
	void AnmationObjectLoad();

	GameEngineImage* Test = nullptr;
	GameEngineImage* HouseFront = nullptr;
	GameEngineImage* Move0 = nullptr;
	GameEngineImage* Move1 = nullptr;
	GameEngineImage* Stair = nullptr;
	GameEngineImage* Machinegun = nullptr;
	GameEngineImage* BoomBridge = nullptr;
	GameEngineImage* BeforeBoss = nullptr;
	GameEngineImage* Boss = nullptr;
	GameEngineImage* Scuttle = nullptr;
	GameEngineImage* UncleRoom = nullptr;
	GameEngineImage* Shop = nullptr;
	GameEngineImage* Spa = nullptr;
	GameEngineImage* Smith = nullptr;
	GameEngineImage* SkyRoom = nullptr;
	GameEngineImage* SaveRoom = nullptr;
};