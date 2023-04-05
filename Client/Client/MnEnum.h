#pragma once
enum class eSceneType {
	Title,
	MainMenu,
	play,
	Stage1,
	end,
	Tool,
	Max,
};

enum class eLayerType {
	BG,
	Tile,
	Monster,
	Player,
	Effect,
	Ground,
	Portal,
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
	Rigidbody,
	Audio,
	Max,
};