#pragma once
enum class eSceneType {
	Title,
	MainMenu,
	play,
	Stage1,
	stage1_2,
	stage1_3,
	stage1_Boss,
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
	Portal,
	Attack,
	Throws,
	Effect,
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