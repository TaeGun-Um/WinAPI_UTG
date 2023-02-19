#pragma once

// Ό³Έν :
class Boss_Boom
{
public:
	// constrcuter destructer
	Boss_Boom();
	~Boss_Boom();

	// delete Function
	Boss_Boom(const Boss_Boom& _Other) = delete;
	Boss_Boom(Boss_Boom&& _Other) noexcept = delete;
	Boss_Boom& operator=(const Boss_Boom& _Other) = delete;
	Boss_Boom& operator=(Boss_Boom&& _Other) noexcept = delete;

protected:

private:

};

