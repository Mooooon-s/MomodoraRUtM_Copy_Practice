#pragma once
enum class eSceneType {
	Title,
	MainMenu,
	play,
	end,
	Max,
};

enum class eLayerType {
	BG,
	Monster,
	Player,
	Effect,
	Attack,
	UI,
	Max,
};

enum class eComponentType 
{
	Transform,
	SpriteRenderer,
	Animator,
	Collider,
	Audio,
	Max,
};

enum class eDir
{
	R,
	L,
};