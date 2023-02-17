#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class UncleRoom_Sea : public GameEngineActor
{
public:
	// constrcuter destructer
	UncleRoom_Sea();
	~UncleRoom_Sea();

	// delete Function
	UncleRoom_Sea(const UncleRoom_Sea& _Other) = delete;
	UncleRoom_Sea(UncleRoom_Sea&& _Other) noexcept = delete;
	UncleRoom_Sea& operator=(const UncleRoom_Sea& _Other) = delete;
	UncleRoom_Sea& operator=(UncleRoom_Sea&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

