#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : 작은 탑
class Building0 : public GameEngineActor
{
public:
	// constrcuter destructer
	Building0();
	~Building0();

	// delete Function
	Building0(const Building0& _Other) = delete;
	Building0(Building0&& _Other) noexcept = delete;
	Building0& operator=(const Building0& _Other) = delete;
	Building0& operator=(Building0&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

