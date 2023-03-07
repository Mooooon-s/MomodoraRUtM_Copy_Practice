#include "MnArsonist.h"
#include "MnResources.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnTransform.h"

namespace Mn
{
	Arsonist::Arsonist()
		:_Image(nullptr)
		,_Animator(nullptr)
	{
	}
	Arsonist::~Arsonist()
	{
	}
	void Arsonist::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(400.0f, 400.0f));
		_Animator = AddComponent<Animator>();

		_Image = Resources::Load<Image>(L"Arsonist", L"..\\Resources\\Arsonist_Move.bmp");
		_Animator->CreateAnimation(L"walk_Right", _Image, Vector2::Zero, 13, 13,7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"walk_Left", _Image, Vector2(0,64), 13, 13, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Back_Step_Right", _Image, Vector2(0,64*2), 13, 13, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Back_Step_Left", _Image, Vector2(0,64*3), 13, 13, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"to_Charge_Right", _Image, Vector2(0, 64 * 4), 13, 13, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"to_Charge_Left", _Image, Vector2(0, 64 * 5), 13, 13, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Charge_Right", _Image, Vector2(0, 64 * 6), 13, 13, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Charge_Left", _Image, Vector2(0, 64 * 7), 13, 13, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Fire_Right", _Image, Vector2(0, 64 * 8), 13, 13, 12, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Fire_Left", _Image, Vector2(0, 64 * 9), 13, 13, 12, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Hurt_right", _Image, Vector2(0, 64 * 10), 13, 13, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Fire_Left", _Image, Vector2(48, 64 * 10), 13, 13, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"stab_Right", _Image, Vector2(0, 64 * 11), 13, 13, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"stab_Left", _Image, Vector2(0, 64 * 12), 13, 13, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Idle_Right", _Image, Vector2(0, 64 * 13), 13, 13, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Idle_Left", _Image, Vector2(0, 64 * 14), 13, 13, 6, Vector2::Zero, 0.08);
		
		_Image = Resources::Load<Image>(L"Arsonist_Attack", L"..\\Resources\\Arsonist_Attack.bmp");
		_Animator->CreateAnimation(L"Swip_Left", _Image, Vector2::Zero, 15, 2, 14,Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Swip_Right", _Image, Vector2(0,64), 15, 2, 14, Vector2::Zero, 0.08);

		_Animator->Play(L"Idle_Right",true);
		GameObject::Initialize();
	}
	void Arsonist::Update()
	{
		GameObject::Update();
	}
	void Arsonist::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Arsonist::Release()
	{
		GameObject::Release();
	}
}
