#include "MnLupiar.h"
#include "MnAnimator.h"
#include "MnComponent.h"
#include "MnResources.h"
namespace Mn
{
	Lupiar::Lupiar()
		: _Image(nullptr)
		, _Animator(nullptr)
	{
	}
	Lupiar::~Lupiar()
	{
	}
	void Lupiar::Initialize()
	{
		//48 48
		GameObject::SetName(L"Boss");
		_Image = Resources::Load<Image>(L"Lupiar", L"..\\Resources\\Lupiar_1.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Lupiar_Idle_Left", _Image, Vector2::Zero, 8, 6, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Idle_Right", _Image, Vector2(0,48), 8, 6, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Roll_Left", _Image, Vector2(0,48*2), 8, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Roll_Right", _Image, Vector2(0,48*3), 8, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Hurt_Left", _Image, Vector2(0,48*4), 8, 6, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Hurt_Right", _Image, Vector2(0,48*5), 8, 6, 1, Vector2::Zero, 0.08);
		
		//128 96
		_Image = Resources::Load<Image>(L"Lupiar_Attack_1", L"..\\Resources\\Lupiar_2.bmp");
		_Animator->CreateAnimation(L"Lupiar_Attack1_Left", _Image, Vector2::Zero, 9, 2, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Attack1_Right", _Image, Vector2(0,96), 9, 2, 9, Vector2::Zero, 0.08);
		//80,48
		_Image = Resources::Load<Image>(L"Lupiar_Attack_2", L"..\\Resources\\Lupiar_3.bmp");
		_Animator->CreateAnimation(L"Lupiar_Attack2_Left", _Image, Vector2::Zero, 10, 2, 10, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Attack2_Right", _Image, Vector2(0,48), 10, 2, 10, Vector2::Zero, 0.08);
		//80,48
		_Image = Resources::Load<Image>(L"Lupiar_Attack_3", L"..\\Resources\\Lupiar_4.bmp");
		_Animator->CreateAnimation(L"Lupiar_Attack3_Left", _Image, Vector2::Zero, 18, 2, 18, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Attack3_Right", _Image, Vector2(0, 48), 18, 2, 18, Vector2::Zero, 0.08);
		//92 96
		_Image = Resources::Load<Image>(L"Lupiar_Attack_4", L"..\\Resources\\Lupiar_5.bmp");
		_Animator->CreateAnimation(L"Lupiar_Attack4_Left", _Image, Vector2::Zero, 9, 2, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Attack4_Left", _Image, Vector2(0,96), 9, 2, 9, Vector2::Zero, 0.08);

		_Animator->Play(L"Lupiar_Idle_Right", true);
	}
	void Lupiar::Update()
	{
		GameObject::Update();
	}
	void Lupiar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Lupiar::Release()
	{
		GameObject::Release();
	}
	void Lupiar::OnCollisionEnter(Collider* other)
	{
	}
	void Lupiar::OnCollisionStay(Collider* other)
	{
	}
	void Lupiar::OnCollisionExit(Collider* other)
	{
	}
}