#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : House 가구
class House_Interior : public GameEngineActor
{
public:
	// constrcuter destructer
	House_Interior();
	~House_Interior();

	// delete Function
	House_Interior(const House_Interior& _Other) = delete;
	House_Interior(House_Interior&& _Other) noexcept = delete;
	House_Interior& operator=(const House_Interior& _Other) = delete;
	House_Interior& operator=(House_Interior&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

