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
	Ground,
	Tile,
	Monster,
	NPC,
	Player,
	Effect,
	Portal,
	Attack,
	Throws,
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