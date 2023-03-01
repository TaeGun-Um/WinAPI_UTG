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
	PlayerEffect,		 // 1
	PlayerAttack,        // 2
	PlayerPistolAttack,  // 3
	Monster,             // 4
	MonsterAttack,       // 5
	Spawner,             // 6
	Ground,              // 7
	Effect,              // 8
	Trigger,			 // 9
	Item,				 // 10
};

// Enum class
// Enum�� �ڷ����� ������ ���Ѿ��ϴ� Enum
// �Ϲ����� Enum�� ����Ϸ����� ��, �ڿ������� casting�� ����������,
// Enum class�� casting�� �������� �ʴ´�.
// casting�� ����ϸ� ����ؾ� �Ѵ�.