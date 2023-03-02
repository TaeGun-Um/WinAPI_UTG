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
	PikeBall,            // 4
	Monster,             // 5
	MonsterAttack,       // 6
	Spawner,             // 7
	Ground,              // 8
	Effect,              // 9
	Trigger,			 // 10
	Item,				 // 11
	Equip,               // 12
};

// Enum class
// Enum�� �ڷ����� ������ ���Ѿ��ϴ� Enum
// �Ϲ����� Enum�� ����Ϸ����� ��, �ڿ������� casting�� ����������,
// Enum class�� casting�� �������� �ʴ´�.
// casting�� ����ϸ� ����ؾ� �Ѵ�.