#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class UncleRoom_Front : public GameEngineActor
{
public:
	// constrcuter destructer
	UncleRoom_Front();
	~UncleRoom_Front();

	// delete Function
	UncleRoom_Front(const UncleRoom_Front& _Other) = delete;
	UncleRoom_Front(UncleRoom_Front&& _Other) noexcept = delete;
	UncleRoom_Front& operator=(const UncleRoom_Front& _Other) = delete;
	UncleRoom_Front& operator=(UncleRoom_Front&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

