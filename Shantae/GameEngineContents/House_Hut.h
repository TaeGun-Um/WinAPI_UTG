#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : House ���� ���
class House_Hut : public GameEngineActor
{
public:
	// constrcuter destructer
	House_Hut();
	~House_Hut();

	// delete Function
	House_Hut(const House_Hut& _Other) = delete;
	House_Hut(House_Hut&& _Other) noexcept = delete;
	House_Hut& operator=(const House_Hut& _Other) = delete;
	House_Hut& operator=(House_Hut&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

