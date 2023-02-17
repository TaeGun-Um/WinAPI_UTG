#pragma once

enum class RenderOrder
{
	BackGround, // 0
	Object,     // 1
	Monster,    // 2
	Player,     // 3
	Map,        // 4
	Effect,     // 5
	UI,         // 6
};

// Collision �׷�ȭ�� ���� Enum �߰�
enum class CollisionOrder
{
	Player,         // 0
	PlayerAttack,   // 1
	Monster,        // 2
	MonsterAttack,  // 3
	Spawner,        // 4
	Ground,         // 5
	Effect,         // 6
	Trigger,
};

// Enum class
// Enum�� �ڷ����� ������ ���Ѿ��ϴ� Enum
// �Ϲ����� Enum�� ����Ϸ����� ��, �ڿ������� casting�� ����������,
// Enum class�� casting�� �������� �ʴ´�.
// casting�� ����ϸ� ����ؾ� �Ѵ�.