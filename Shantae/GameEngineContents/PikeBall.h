#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// ???? :
class PikeBall : public GameEngineActor
{
public:
	// constrcuter destructer
	PikeBall();
	~PikeBall();

	// delete Function
	PikeBall(const PikeBall& _Other) = delete;
	PikeBall(PikeBall&& _Other) noexcept = delete;
	PikeBall& operator=(const PikeBall& _Other) = delete;
	PikeBall& operator=(PikeBall&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void MoveCalculation(float _DeltaTime);
	void CollisionCheck(float _DeltaTime);
	void ApplyScore();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	float4 UpPos = float4::Zero;

	GameEngineSoundPlayer BGMPlayer;

	int SoundCount = 1;
	int UpCount = 1;

	bool IsUp = false;

};

