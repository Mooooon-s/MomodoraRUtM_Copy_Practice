#pragma once
enum class eSceneType {
	Title,
	MainMenu,
	play,
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