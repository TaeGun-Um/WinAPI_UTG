#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : House에서 자는 Shantae (Animation)
class Shantae_Pajamas : public GameEngineActor
{
public:
	static GameEngineRender* AnimationRender;

	// constrcuter destructer
	Shantae_Pajamas();
	~Shantae_Pajamas();

	// delete Function
	Shantae_Pajamas(const Shantae_Pajamas& _Other) = delete;
	Shantae_Pajamas(Shantae_Pajamas&& _Other) noexcept = delete;
	Shantae_Pajamas& operator=(const Shantae_Pajamas& _Other) = delete;
	Shantae_Pajamas& operator=(Shantae_Pajamas&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

