#pragma once
enum class eSceneType {
	Title,
	MainMenu,
	play,
	Stage1,
	stage1_2,
	stage1_3,
	stage1_Boss,
	stage2_1,
	stage2_2,
	stage2_Plus,
	stage2_3,
	stage3_1,
	stage3_1_1,
	stage3_2,
	stage3_3,
	end,
	Tool,
	Max,
};

enum class eLayerType {
	BG,
	Trriger,
	Tile,
	Ground,
	ChargeEffect,
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