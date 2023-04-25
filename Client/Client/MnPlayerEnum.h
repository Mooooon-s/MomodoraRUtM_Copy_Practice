#pragma once

enum class ePlayerStatus
{
	Idle,
	Move,
	Hurt,
	Jump,
	Fall,
	Attack,
	Crouch,
	Shoot,
	Roll,
	UseItem,
	Death,
};

enum class eDir
{
	R,
	L,
};