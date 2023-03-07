#include "MnKaho_Human.h"
#include "MnResources.h"
#include "MnComponent.h"
#include "MnTransform.h"
#include "MnAnimator.h"
#include "MnCollider.h"

namespace Mn
{
	Kaho_Human::Kaho_Human()
		:_Animator(nullptr)
		, _Image(nullptr)
		, _col(24)
		, _row(44)
	{
	}
	Kaho_Human::~Kaho_Human()
	{
	}
	void Kaho_Human::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(200.0f,400.0f));

		Collider* collider = AddComponent<Collider>();
		collider->Center(Vector2(-24.0f * 3, -48.0f * 3));

		Image* _Image = Resources::Load<Image>(L"Kaho", L"..\\Resources\\Kaho_Human.bmp");
		_Animator = AddComponent<Animator>();
		//Kaho_Human------------------------------------------------------------------------------------------
		//Move Right
		_Animator->CreateAnimation(L"Idle_Right", _Image, Vector2::Zero, _col, _row, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Run_Right", _Image, Vector2(0, 48), _col, _row, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Start_Run_Right", _Image, Vector2(0, (48 * 2)), _col, _row, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"End_Run_Right", _Image, Vector2(0, (48 * 3)), _col, _row, 6, Vector2::Zero, 0.08);
		//Move Left
		_Animator->CreateAnimation(L"Idle_Left", _Image, Vector2(0, (48 * 4)), _col, _row, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Run_Left", _Image, Vector2(0, (48 * 5)), _col, _row, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Start_Run_Left", _Image, Vector2(0, (48 * 6)), _col, _row, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"End_Run_Left", _Image, Vector2(0, (48 * 7)), _col, _row, 6, Vector2::Zero, 0.08);
		//Hurt
		_Animator->CreateAnimation(L"Hurt_Right", _Image, Vector2(96, (48 * 2)), _col, _row, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Hurt_Left", _Image, Vector2(142, (48 * 2)), _col, _row, 1, Vector2::Zero, 0.08);
		//Crouch
		_Animator->CreateAnimation(L"Crouch_Right", _Image, Vector2(0, (48 * 8)), _col, _row, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Crouch_Left", _Image, Vector2(0, (48 * 9)), _col, _row, 4, Vector2::Zero, 0.08);
		//Rise
		_Animator->CreateAnimation(L"Rise_Right", _Image, Vector2(0, (48 * 10)), _col, _row, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Rise_Left", _Image, Vector2(0, (48 * 11)), _col, _row, 2, Vector2::Zero, 0.08);
		//Jump
		_Animator->CreateAnimation(L"Jump_Right", _Image, Vector2(0, (48 * 12)), _col, _row, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Jump_Left", _Image, Vector2(0, (48 * 13)), _col, _row, 3, Vector2::Zero, 0.08);
		//Fall
		_Animator->CreateAnimation(L"Fall_Right", _Image, Vector2(0, (48 * 14)), _col, _row, 5, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Fall_Left", _Image, Vector2(0, (48 * 15)), _col, _row, 5, Vector2::Zero, 0.08);
		//Rolling
		_Animator->CreateAnimation(L"Roll_Right", _Image, Vector2(0, (48 * 16)), _col, _row, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Roll_Left", _Image, Vector2(0, (48 * 17)), _col, _row, 8, Vector2::Zero, 0.08);
		//Range Attack
		_Animator->CreateAnimation(L"Range_Attack_Right", _Image, Vector2(0, (48 * 18)), _col, _row, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Range_Attack_Left", _Image, Vector2(0, (48 * 19)), _col, _row, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Air_Range_Attack_Right", _Image, Vector2(288, (48 * 18)), _col, _row, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Air_Range_Attack_Left", _Image, Vector2(288, (48 * 19)), _col, _row, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Crouch_Range_Attack_Right", _Image, Vector2(576, (48 * 18)), _col, _row, 6, Vector2(0.0f, 12.0f), 0.08);
		_Animator->CreateAnimation(L"Crouch_Range_Attack_Left", _Image, Vector2(576, (48 * 19)), _col, _row, 6, Vector2(0.0f, 12.0f), 0.08);
		//Melee Attack_1
		_Animator->CreateAnimation(L"Melee_Attack_1_Right", _Image, Vector2(0, (48 * 20)), _col, _row, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Melee_Attack_1_Left", _Image, Vector2(0, (48 * 21)), _col, _row, 7, Vector2::Zero, 0.08);
		//Air_Melee_Attack_1
		_Animator->CreateAnimation(L"Air_Melee_Attack_Right", _Image, Vector2(0, (48 * 22)), _col, _row, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Air_Melee_Attack_Left", _Image, Vector2(0, (48 * 23)), _col, _row, 7, Vector2::Zero, 0.08);

		//Melee_Attack_2
		_Animator->CreateAnimation(L"Melee_Attack_2_Right", _Image, Vector2(0, (48 * 24)), _col, _row, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Melee_Attack_2_Left", _Image, Vector2(0, (48 * 25)), _col, _row, 7, Vector2::Zero, 0.08);
		//Melee_Attack_3
		_Animator->CreateAnimation(L"Melee_Attack_3_Right", _Image, Vector2(0, (48 * 26)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Melee_Attack_3_Left", _Image, Vector2(0, (48 * 27)), _col, _row, 11, Vector2::Zero, 0.08);
		//Leder_Up
		_Animator->CreateAnimation(L"Leader_Up", _Image, Vector2(0, (48 * 28)), _col, _row, 6, Vector2::Zero, 0.08);
		//Leder_Down
		_Animator->CreateAnimation(L"Leader_Down", _Image, Vector2(0, (48 * 29)), _col, _row, 3, Vector2::Zero, 0.08);
		//Use_Item
		_Animator->CreateAnimation(L"Use_Item_Right", _Image, Vector2(0, (48 * 30)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Use_Item_Left", _Image, Vector2(0, (48 * 31)), _col, _row, 11, Vector2::Zero, 0.08);
		//Dash
		_Animator->CreateAnimation(L"Dash_Right", _Image, Vector2(192, (48 * 4)), _col, _row, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Dash_Left", _Image, Vector2(240, (48 * 4)), _col, _row, 1, Vector2::Zero, 0.08);
		//preDash
		_Animator->CreateAnimation(L"PreDash_Right", _Image, Vector2(0, (48 * 32)), _col, _row, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"PostDash_Right", _Image, Vector2(144, (48 * 32)), _col, _row, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"PreDash_Left", _Image, Vector2(0, (48 * 33)), _col, _row, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"PostDash_Left", _Image, Vector2(144, (48 * 33)), _col, _row, 3, Vector2::Zero, 0.08);
		//soft_Landing
		_Animator->CreateAnimation(L"soft_Landing_Right", _Image, Vector2(0, (48 * 34)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"soft_Landing_Left", _Image, Vector2(0, (48 * 35)), _col, _row, 11, Vector2::Zero, 0.08);
		//Hard_Landing
		_Animator->CreateAnimation(L"Hard_Landing_Right", _Image, Vector2(0, (48 * 36)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Hard_Landing_Left", _Image, Vector2(0, (48 * 37)), _col, _row, 11, Vector2::Zero, 0.08);
		//Look_Around
		_Animator->CreateAnimation(L"Look_Around_Right", _Image, Vector2(0, (48 * 38)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Look_Around_Left", _Image, Vector2(0, (48 * 39)), _col, _row, 11, Vector2::Zero, 0.08);
		//Spin
		_Animator->CreateAnimation(L"Spin_Right", _Image, Vector2(0, (48 * 40)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Spin_Left", _Image, Vector2(0, (48 * 41)), _col, _row, 11, Vector2::Zero, 0.08);

		//Death
		_Animator->CreateAnimation(L"Death_Right", _Image, Vector2(0, (48 * 42)), _col, _row, 24, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Death_Left", _Image, Vector2(0, (48 * 43)), _col, _row, 24, Vector2::Zero, 0.08);

		_Animator->Play(L"Idle_Right", true);
		GameObject::Initialize();
	}
	void Kaho_Human::Update()
	{
		GameObject::Update();
	}
	void Kaho_Human::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Kaho_Human::Release()
	{
		GameObject::Release();
	}
}