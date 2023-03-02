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

// Collision 그룹화를 위한 Enum 추가
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
// Enum의 자료형을 무조건 지켜야하는 Enum
// 일반적인 Enum은 사용하려고할 때, 자연스럽게 casting이 지원되지만,
// Enum class는 casting을 지원하지 않는다.
// casting을 명시하며 사용해야 한다.