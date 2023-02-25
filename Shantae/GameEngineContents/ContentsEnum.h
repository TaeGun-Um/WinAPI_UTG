#pragma once

enum class RenderOrder
{
	BackGround,		 // 0
	Object,			 // 1
	Monster,		 // 2
	Player,			 // 3
	AnimationObject, // 4
	Map,			 // 5
	Effect,			 // 6
	UI,				 // 7
	Box,			 // 8
};

// Collision �׷�ȭ�� ���� Enum �߰�
enum class CollisionOrder
{
	Player,              // 0
	PlayerAttack,        // 1
	PlayerPistolAttack,  // 2
	Monster,             // 3
	MonsterAttack,       // 4
	Spawner,             // 5
	Ground,              // 6
	Effect,              // 7
	Trigger,			 // 8
};

// Enum class
// Enum�� �ڷ����� ������ ���Ѿ��ϴ� Enum
// �Ϲ����� Enum�� ����Ϸ����� ��, �ڿ������� casting�� ����������,
// Enum class�� casting�� �������� �ʴ´�.
// casting�� ����ϸ� ����ؾ� �Ѵ�.