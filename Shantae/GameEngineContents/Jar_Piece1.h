#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Jar_Piece1 : public GameEngineActor
{
public:
	// constrcuter destructer
	Jar_Piece1();
	~Jar_Piece1();

	// delete Function
	Jar_Piece1(const Jar_Piece1& _Other) = delete;
	Jar_Piece1(Jar_Piece1&& _Other) noexcept = delete;
	Jar_Piece1& operator=(const Jar_Piece1& _Other) = delete;
	Jar_Piece1& operator=(Jar_Piece1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

