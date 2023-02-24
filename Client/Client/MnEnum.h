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
	UI,
	Max,
};

enum class eComponentType 
{
	Transform,
	Collider,
	SpriteRenderer,
	Animator,
	Audio,
	Max,
};