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
};

enum class eDir
{
	R,
	L,
};