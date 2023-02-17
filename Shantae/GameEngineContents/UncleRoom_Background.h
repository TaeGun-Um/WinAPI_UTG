#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class UncleRoom_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	UncleRoom_Background();
	~UncleRoom_Background();

	// delete Function
	UncleRoom_Background(const UncleRoom_Background& _Other) = delete;
	UncleRoom_Background(UncleRoom_Background&& _Other) noexcept = delete;
	UncleRoom_Background& operator=(const UncleRoom_Background& _Other) = delete;
	UncleRoom_Background& operator=(UncleRoom_Background&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

