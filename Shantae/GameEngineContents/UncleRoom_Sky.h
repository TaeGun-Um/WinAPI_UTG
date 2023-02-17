#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class UncleRoom_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	UncleRoom_Sky();
	~UncleRoom_Sky();

	// delete Function
	UncleRoom_Sky(const UncleRoom_Sky& _Other) = delete;
	UncleRoom_Sky(UncleRoom_Sky&& _Other) noexcept = delete;
	UncleRoom_Sky& operator=(const UncleRoom_Sky& _Other) = delete;
	UncleRoom_Sky& operator=(UncleRoom_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

