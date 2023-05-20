#include "MnKaho_Human.h"
#include "MnResources.h"
#include "MnInput.h"
#include "MnTime.h"

#include "MnComponent.h"
#include "MnTransform.h"
#include "MnAnimator.h"
#include "MnCollider.h"
#include "MnRigidbody.h"

#include "MnSceneManager.h"
#include "MnScene.h"

#include "MnObject.h"
#include "MnArrow.h"
#include "MnKnife.h"
#include "MnMeleeEffect.h"
#include "MnMonMeleeAttack.h"
#include "MnStaff.h"
#include "MnBomb.h"

#include "MnFireBall.h"
#include "MnFireFlame.h"
#include "MnFlame.h"

#include "MnLupiarBall.h"
#include "MnMagArrow.h"

#include "MnChargeEffect.h"
#include "MnPrayEffect.h"
#include "MnItemBox.h"
#include "MnWall.h"

namespace Mn
{
	Kaho_Human::Kaho_Human()
		: GameObject()
		, _PlayerStatus(ePlayerStatus::Idle)
		, _Animator(nullptr)
		, _Rigidbody(nullptr)
		, _Image(nullptr)
		, _PrayEffect(nullptr)
		, _DashCharge(0.0f)
		, _HurtTime(0.0f)
		, _AlphaTime(0.0f)
		, _DamageTime(0.0f)
		, _Jumpforce(550.0f)
		, _MoveSpeed(0.0f)
		, _CoolTime(0.0f)
		, _Hp(100.0f)
		, _DashOn(true)
		, _Switch(false)
		, _Combo(false)
		, _IsCrouch(false)
		, _IsGround(true)
		, _GetDamage(true)
		, _Death(false)
		, _Dir(eDir::R)
		, _col(24)
		, _row(46)
		, _AlphaDegree(90)
		, _DoubleJump(0)
		, _ComboCount(0)
		, _RevivalPos(Vector2::Zero)
		, _SoundPack()
		, _On(false)
	{
	}
	Kaho_Human::~Kaho_Human()
	{
	}
	void Kaho_Human::Initialize()
	{
		GameObject::SetName(L"Player");
		Transform* tr = GetComponent<Transform>();


		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(0.3f);
		_Rigidbody->SetGround(false);

		Collider* collider = AddComponent<Collider>();
		collider->Center(Vector2(-12.0f * 3, -40.0f * 3));
		collider->Size(Vector2(24.0f * 3, 38.0f * 3));

		Image* _Image = Resources::Load<Image>(L"Kaho", L"..\\Resources\\Kaho_Human_alpha_1.bmp");
		_Animator = AddComponent<Animator>();
		//-------------------------------------------------------------------------------------------------------------
		//												
		//												Kaho_Human Animation
		// 
		// ------------------------------------------------------------------------------------------------------------
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
		_Animator->CreateAnimation(L"Melee_Attack_1_Right", _Image, Vector2(0, (48 * 20)), _col, _row, 7, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Melee_Attack_1_Left", _Image, Vector2(0, (48 * 21)), _col, _row, 7, Vector2::Zero, 0.06);
		//Air_Melee_Attack_1
		_Animator->CreateAnimation(L"Air_Melee_Attack_Right", _Image, Vector2(0, (48 * 22)), _col, _row, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Air_Melee_Attack_Left", _Image, Vector2(0, (48 * 23)), _col, _row, 7, Vector2::Zero, 0.08);

		//Melee_Attack_2
		_Animator->CreateAnimation(L"Melee_Attack_2_Right", _Image, Vector2(0, (48 * 24)), _col, _row, 7, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Melee_Attack_2_Left", _Image, Vector2(0, (48 * 25)), _col, _row, 7, Vector2::Zero, 0.06);
		//Melee_Attack_3
		_Animator->CreateAnimation(L"Melee_Attack_3_Right", _Image, Vector2(0, (48 * 26)), _col, _row, 11, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Melee_Attack_3_Left", _Image, Vector2(0, (48 * 27)), _col, _row, 11, Vector2::Zero, 0.06);
		//Leder_Up
		_Animator->CreateAnimation(L"Leader_Up", _Image, Vector2(0, (48 * 28)), _col, _row, 6, Vector2::Zero, 0.08);
		//Leder_Down
		_Animator->CreateAnimation(L"Leader_Down", _Image, Vector2(0, (48 * 29)), _col, _row, 3, Vector2::Zero, 0.08);
		//Use_Item
		_Animator->CreateAnimation(L"Use_Item_Right", _Image, Vector2(0, (48 * 30)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Use_Item_Left", _Image, Vector2(0, (48 * 31)), _col, _row, 11, Vector2::Zero, 0.08);
		//Dash
		_Animator->CreateAnimation(L"Dash_Right", _Image, Vector2(48*4, (48 * 2)), _col, _row, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Dash_Left", _Image, Vector2(48*5, (48 * 2)), _col, _row, 1, Vector2::Zero, 0.08);
		//preDash
		_Animator->CreateAnimation(L"PreDash_Right", _Image, Vector2(0, (48 * 32)), _col, _row, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"PostDash_Right", _Image, Vector2(144, (48 * 32)), _col, _row, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"PreDash_Left", _Image, Vector2(0, (48 * 33)), _col, _row, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"PostDash_Left", _Image, Vector2(144, (48 * 33)), _col, _row, 3, Vector2::Zero, 0.08);
		//soft_Landing
		_Animator->CreateAnimation(L"soft_Landing_Right", _Image, Vector2(0, (48 * 34)), _col, _row, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"soft_Landing_Left", _Image, Vector2(0, (48 * 35)), _col, _row, 4, Vector2::Zero, 0.08);
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

		_Animator->CreateAnimation(L"Pray_Right", _Image, Vector2(0, (48 * 44)), _col, _row, 10, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Kaho_Pray", L"..\\Resources\\Kaho_Pray_Left_alpha.bmp");
		_Animator->CreateAnimation(L"Pray_Left", _Image, Vector2(0,0), 10, 1, 10, Vector2::Zero, 0.08);

		//-------------------------------------------------------------------------------------------------------------------
		//
		//													Events
		// 
		//-------------------------------------------------------------------------------------------------------------------
		//ComboAttack
		_Animator->GetStartEvent(L"Melee_Attack_1_Right") = std::bind(&Kaho_Human::attackStart, this);
		_Animator->GetStartEvent(L"Melee_Attack_1_Left") = std::bind(&Kaho_Human::attackStart, this);
		_Animator->GetCompleteEvent(L"Melee_Attack_1_Right") = std::bind(&Kaho_Human::attackComplete, this);
		_Animator->GetCompleteEvent(L"Melee_Attack_1_Left") = std::bind(&Kaho_Human::attackComplete, this);
		
		_Animator->GetStartEvent(L"Melee_Attack_2_Right") = std::bind(&Kaho_Human::attackCombo1Start, this);
		_Animator->GetStartEvent(L"Melee_Attack_2_Left") = std::bind(&Kaho_Human::attackCombo1Start, this);
		_Animator->GetCompleteEvent(L"Melee_Attack_2_Right") = std::bind(&Kaho_Human::attackCombo1Complete, this);
		_Animator->GetCompleteEvent(L"Melee_Attack_2_Left") = std::bind(&Kaho_Human::attackCombo1Complete, this);
		
		_Animator->GetStartEvent(L"Melee_Attack_3_Right") = std::bind(&Kaho_Human::attackCombo2Start, this);
		_Animator->GetStartEvent(L"Melee_Attack_3_Left") = std::bind(&Kaho_Human::attackCombo2Start, this);
		_Animator->GetCompleteEvent(L"Melee_Attack_3_Right") = std::bind(&Kaho_Human::attackCombo2Complete, this);
		_Animator->GetCompleteEvent(L"Melee_Attack_3_Left") = std::bind(&Kaho_Human::attackCombo2Complete, this);

		_Animator->GetStartEvent(L"Air_Melee_Attack_Right") = std::bind(&Kaho_Human::airAttackStart, this);
		_Animator->GetStartEvent(L"Air_Melee_Attack_Left") = std::bind(&Kaho_Human::airAttackStart, this);
		_Animator->GetCompleteEvent(L"Air_Melee_Attack_Right") = std::bind(&Kaho_Human::airAttackComplete, this);
		_Animator->GetCompleteEvent(L"Air_Melee_Attack_Left") = std::bind(&Kaho_Human::airAttackComplete, this);
		//RangeAttack
		_Animator->GetStartEvent(L"Range_Attack_Right") = std::bind(&Kaho_Human::beforeRange, this);
		_Animator->GetCompleteEvent(L"Range_Attack_Right") = std::bind(&Kaho_Human::afterRange, this);
		_Animator->GetStartEvent(L"Range_Attack_Left") = std::bind(&Kaho_Human::beforeRange, this);
		_Animator->GetCompleteEvent(L"Range_Attack_Left") = std::bind(&Kaho_Human::afterRange, this);
		_Animator->GetStartEvent(L"Air_Range_Attack_Right") = std::bind(&Kaho_Human::airRangeStart, this);
		_Animator->GetCompleteEvent(L"Air_Range_Attack_Right") = std::bind(&Kaho_Human::airRangeComplete, this);
		_Animator->GetStartEvent(L"Air_Range_Attack_Left") = std::bind(&Kaho_Human::airRangeStart, this);
		_Animator->GetCompleteEvent(L"Air_Range_Attack_Left") = std::bind(&Kaho_Human::airRangeComplete, this);
		_Animator->GetStartEvent(L"Crouch_Range_Attack_Right") = std::bind(&Kaho_Human::crouchRangeStart, this);
		_Animator->GetStartEvent(L"Crouch_Range_Attack_Left") = std::bind(&Kaho_Human::crouchRangeStart, this);
		_Animator->GetCompleteEvent(L"Crouch_Range_Attack_Right") = std::bind(&Kaho_Human::crouchRangeComplete, this);
		_Animator->GetCompleteEvent(L"Crouch_Range_Attack_Left") = std::bind(&Kaho_Human::crouchRangeComplete, this);
		//Roll
		_Animator->GetCompleteEvent(L"Roll_Right") = std::bind(&Kaho_Human::afterRoll, this);
		_Animator->GetCompleteEvent(L"Roll_Left") = std::bind(&Kaho_Human::afterRoll, this);
		//useItem
		_Animator->GetCompleteEvent(L"Use_Item_Right") = std::bind(&Kaho_Human::afterUseItem, this);
		_Animator->GetCompleteEvent(L"Use_Item_Left") = std::bind(&Kaho_Human::afterUseItem, this);
		_Animator->FindAnimation(L"Use_Item_Right")->GetSprite(5)._Events._FrameEvent._Event = std::bind(&Kaho_Human::useItem, this);
		_Animator->FindAnimation(L"Use_Item_Left")->GetSprite(5)._Events._FrameEvent._Event = std::bind(&Kaho_Human::useItem, this);
		//Rise Up
		_Animator->GetCompleteEvent(L"Rise_Right") = std::bind(&Kaho_Human::riseUp, this);
		_Animator->GetCompleteEvent(L"Rise_Left") = std::bind(&Kaho_Human::riseUp, this);
		//Stop Run
		_Animator->GetCompleteEvent(L"End_Run_Right") = std::bind(&Kaho_Human::endRun, this);
		_Animator->GetCompleteEvent(L"End_Run_Left") = std::bind(&Kaho_Human::endRun, this);

		_Animator->GetCompleteEvent(L"soft_Landing_Right") = std::bind(&Kaho_Human::landingComplete, this);
		_Animator->GetCompleteEvent(L"soft_Landing_Left") = std::bind(&Kaho_Human::landingComplete, this);

		_Animator->GetCompleteEvent(L"PreDash_Right") = std::bind(&Kaho_Human::preDashComplete, this);
		_Animator->GetCompleteEvent(L"PreDash_Left") = std::bind(&Kaho_Human::preDashComplete, this);
		_Animator->GetCompleteEvent(L"Dash_Right") = std::bind(&Kaho_Human::DashComplete, this);
		_Animator->GetCompleteEvent(L"Dash_Left") = std::bind(&Kaho_Human::DashComplete, this);
		_Animator->GetCompleteEvent(L"PostDash_Right") = std::bind(&Kaho_Human::postDashComplete, this);
		_Animator->GetCompleteEvent(L"PostDash_Left") = std::bind(&Kaho_Human::postDashComplete, this);

		_Animator->FindAnimation(L"Pray_Right")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&Kaho_Human::pray, this);
		_Animator->FindAnimation(L"Pray_Left")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&Kaho_Human::pray, this);
		_Animator->FindAnimation(L"Pray_Right")->GetSprite(7)._Events._FrameEvent._Event = std::bind(&Kaho_Human::pray, this);
		_Animator->FindAnimation(L"Pray_Left")->GetSprite(7)._Events._FrameEvent._Event = std::bind(&Kaho_Human::pray, this);

		_Animator->FindAnimation(L"Run_Right")->GetSprite(1)._Events._FrameEvent._Event = std::bind(&Kaho_Human::walkSound, this);
		_Animator->FindAnimation(L"Run_Right")->GetSprite(5)._Events._FrameEvent._Event = std::bind(&Kaho_Human::walkSound, this);
		_Animator->FindAnimation(L"Run_Left")->GetSprite(1)._Events._FrameEvent._Event = std::bind(&Kaho_Human::walkSound, this);
		_Animator->FindAnimation(L"Run_Left")->GetSprite(5)._Events._FrameEvent._Event = std::bind(&Kaho_Human::walkSound, this);
		
		_Animator->GetCompleteEvent(L"Pray_Right") = std::bind(&Kaho_Human::afterpray, this);
		_Animator->GetCompleteEvent(L"Pray_Left") = std::bind(&Kaho_Human::afterpray, this);
		_Animator->GetCompleteEvent(L"Death_Right") = std::bind(&Kaho_Human::afterDeath, this);
		_Animator->GetCompleteEvent(L"Death_Left") = std::bind(&Kaho_Human::afterDeath, this);

		//----------------------------------------------------------------------------------------------------------------
		//
		//													Sound
		//
		//----------------------------------------------------------------------------------------------------------------
		_SoundPack.push_back(Resources::Load<Sound>(L"Player_Walk_Sound", L"..\\Resources\\Sound\\Kaho_Human\\walk.wav"));
		_SoundPack.push_back(Resources::Load<Sound>(L"Player_Hurt_Sound", L"..\\Resources\\Sound\\Kaho_Human\\Kaho_Hurt.wav"));
		_SoundPack.push_back(Resources::Load<Sound>(L"Player_Pray_Sound", L"..\\Resources\\Sound\\Kaho_Human\\Prey.wav"));
		_SoundPack.push_back(Resources::Load<Sound>(L"Player_UseItem_Sound", L"..\\Resources\\Sound\\Kaho_Human\\Use_Item.wav"));
		_SoundPack.push_back(Resources::Load<Sound>(L"Player_Shoot_Sound", L"..\\Resources\\Sound\\Kaho_Human\\Shoot_Arrow.wav"));
		_SoundPack.push_back(Resources::Load<Sound>(L"Player_Death_Sound", L"..\\Resources\\Sound\\Kaho_Human\\Kaho_Death.wav"));
		_SoundPack.push_back(Resources::Load<Sound>(L"Player_Jump_Sound", L"..\\Resources\\Sound\\Kaho_Human\\Jump.wav"));
		_SoundPack.push_back(Resources::Load<Sound>(L"Player_Roll_Sound", L"..\\Resources\\Sound\\Kaho_Human\\Roll.wav"));
		_SoundPack.push_back(Resources::Load<Sound>(L"Player_AirRoll_Sound", L"..\\Resources\\Sound\\Kaho_Human\\AirRoll.wav"));
		_SoundPack.push_back(Resources::Load<Sound>(L"Player_Attack1_Sound", L"..\\Resources\\Sound\\Kaho_Human\\Melee_1.wav"));
		_SoundPack.push_back(Resources::Load<Sound>(L"Player_Attack2_Sound", L"..\\Resources\\Sound\\Kaho_Human\\Melee_2.wav"));
		_SoundPack.push_back(Resources::Load<Sound>(L"Player_Attack3_Sound", L"..\\Resources\\Sound\\Kaho_Human\\Melee_3.wav"));


		_Animator->Play(L"Idle_Right", true);
		GameObject::Initialize();
	}
	void Kaho_Human::Update()
	{
		if (Input::GetKeyDown(eKeyCode::K) && _On == false)
			_On = true;
		else if (Input::GetKeyDown(eKeyCode::K) && _On == true)
			_On = false;

		if (_RevivalPos == Vector2::Zero)
		{
			Transform* tr = GetComponent<Transform>();
			_RevivalPos = tr->Pos();
		}
		if (GameObject::State()==eState::Active)
		{
			Transform* tr = GetComponent<Transform>();
			_pos = tr->Pos();

			switch (_PlayerStatus)
			{
			case ePlayerStatus::Idle:
				idle();
				break;
			case ePlayerStatus::Move:
				move();
				break;
			case ePlayerStatus::Attack:
				attack();
				break;
			case ePlayerStatus::Shoot:
				shoot();
				break;
			case ePlayerStatus::Crouch:
				crouch();
				break;
			case ePlayerStatus::Jump:
				jump();
				break;
			case ePlayerStatus::Fall:
				fall();
				break;
			case ePlayerStatus::Roll:
				roll();
				break;
			case ePlayerStatus::UseItem:
				//useItem();
				break;
			case ePlayerStatus::Hurt:
				hurt();
				break;
			default:
				break;
			}

			if (_DashOn == false)
			{
				_CoolTime -= Time::DeltaTime();
				if (_CoolTime < 0.0f)
				{
					ChargeEffect* effect = object::Instantiate<ChargeEffect>(Vector2(_pos.x, _pos.y - (24 * 3)), eLayerType::ChargeEffect);
					effect->GetOwnerObject(this);
					_DashOn = true;
				}
			}

			tr->Pos(_pos);
			_AlphaTime += Time::DeltaTime();
			if (_DoubleJump != 0 && _Rigidbody->GetGround() == true)
				_DoubleJump = 0;
			
			if (_Hp <= 0 && _Death==false)
			{
				_SoundPack[(int)eSound::Death]->Play(false);
				_Death = true;
				_PlayerStatus = ePlayerStatus::Death;
				animationCtrl();
			}


			GameObject::Update();
		}
	}
	void Kaho_Human::Render(HDC hdc)
	{
		if (GameObject::State() == eState::Active)
		{
			if (_GetDamage == false)
			{
				alpha();
				_DamageTime += Time::DeltaTime();
			}
			GameObject::Render(hdc);
		}
	}
	void Kaho_Human::Release()
	{
		GameObject::Release();
	}
	//-------------------------------------------------------------------------------------------------------------------
	//
	//													Collider
	// 
	//-------------------------------------------------------------------------------------------------------------------
	void Kaho_Human::OnCollisionEnter(Collider* other)
	{
		if (_Death == false)
		{
			if (other->Owner()->GetName() == L"Enemy" && _GetDamage == true && _PlayerStatus != ePlayerStatus::Roll
				|| other->Owner()->GetName() == L"Obstacle" && _GetDamage == true && _PlayerStatus != ePlayerStatus::Roll)
			{
				_Hp -= 10;
				_GetDamage = false;
				_SoundPack[(int)eSound::Hurt]->Play(false);
				_PlayerStatus = ePlayerStatus::Hurt;
				animationCtrl();
			}
			
			if (other->Owner()->GetName() == L"Boss" && _GetDamage == true && _PlayerStatus != ePlayerStatus::Roll)
			{
				_Hp -= 10;
				_GetDamage = false;
				_SoundPack[(int)eSound::Hurt]->Play(false);
				_PlayerStatus = ePlayerStatus::Hurt;
				animationCtrl();
			}

			if (other->Owner()->GetName() == L"Throws" && _GetDamage == true && _PlayerStatus != ePlayerStatus::Roll)
			{
				if (dynamic_cast<Knife*>(other->Owner()))
				{
					dynamic_cast<Knife*>(other->Owner())->Hit();
					_GetDamage = false;
					_Hp -= 10;
					_SoundPack[(int)eSound::Hurt]->Play(false);
					_PlayerStatus = ePlayerStatus::Hurt;
					animationCtrl();
				}
				if (dynamic_cast<MonMeleeAttack*>(other->Owner())
					|| dynamic_cast<Staff*>(other->Owner())
					|| dynamic_cast<Flame*>(other->Owner())
					|| dynamic_cast<MagArrow*>(other->Owner())
					|| dynamic_cast<FireBall*>(other->Owner())
					|| dynamic_cast<FireFlame*>(other->Owner())
					|| dynamic_cast<LupiarBall*>(other->Owner()))
				{
					_GetDamage = false;
					_Hp -= 10;
					_SoundPack[(int)eSound::Hurt]->Play(false);
					_PlayerStatus = ePlayerStatus::Hurt;
					animationCtrl();
				}
			}
			if (dynamic_cast<Bomb*>(other->Owner()))
			{
				if (dynamic_cast<Bomb*>(other->Owner())->BlowUp() == false)
				{
					_GetDamage = false;
					_Hp -= 10;
					_SoundPack[(int)eSound::Hurt]->Play(false);
					_PlayerStatus = ePlayerStatus::Hurt;
					animationCtrl();
				}
			}



		}
	}
	void Kaho_Human::OnCollisionStay(Collider* other)
	{
		if (_Death == false)
		{
			if (other->Owner()->GetName() == L"Enemy" && _GetDamage == true && _PlayerStatus != ePlayerStatus::Roll)
			{
				_SoundPack[(int)eSound::Hurt]->Play(false);
				_Hp -= 15;
				_GetDamage = false;
				_PlayerStatus = ePlayerStatus::Hurt;
				animationCtrl();
			}

			if (other->Owner()->GetName() == L"Boss" && _GetDamage == true && _PlayerStatus != ePlayerStatus::Roll)
			{
				_SoundPack[(int)eSound::Hurt]->Play(false);
				_Hp -= 15;
				_GetDamage = false;
				_PlayerStatus = ePlayerStatus::Hurt;
				animationCtrl();
			}

			if (other->Owner()->GetName() == L"Bell")
			{
				if (Input::GetKeyDown(eKeyCode::Up))
				{
					if (_Dir == eDir::R)
						_Animator->Play(L"Pray_Right", false);
					else
						_Animator->Play(L"Pray_Left", false);
				}
			}


			if (other->Owner()->GetName() == L"Wall")
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->Pos();
				if (_Dir == eDir::R)
				{
					pos.x -= _MoveSpeed * Time::DeltaTime();
					tr->Pos(pos);
				}
				else
				{
					pos.x += _MoveSpeed * Time::DeltaTime();
					tr->Pos(pos);
				}
			}
		}
	}
	void Kaho_Human::OnCollisionExit(Collider* other)
	{

	}
	//-------------------------------------------------------------------------------------------------------------------
	//
	//													FSM
	// 
	//-------------------------------------------------------------------------------------------------------------------
	void Kaho_Human::animationCtrl()
	{
		switch (_PlayerStatus)
		{
		case ePlayerStatus::Idle:
			if (_Dir == eDir::R)
			{
				_Animator->Play(L"Idle_Right", true);
			}
			else
				_Animator->Play(L"Idle_Left", true);
			break;
		case ePlayerStatus::Move:
			if (_Dir == eDir::R)
				_Animator->Play(L"Run_Right", true);
			else
				_Animator->Play(L"Run_Left", true);
			break;
		case ePlayerStatus::Attack:
			if (_Rigidbody->GetGround()==true)
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Melee_Attack_1_Right", false);
				else
					_Animator->Play(L"Melee_Attack_1_Left", false);
			}
			else
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Air_Melee_Attack_Right", false);
				else
					_Animator->Play(L"Air_Melee_Attack_Left", false);
			}
			break;
		case ePlayerStatus::Shoot:
			if (!_IsCrouch && _Rigidbody->GetGround() == true)
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Range_Attack_Right", false);
				else
					_Animator->Play(L"Range_Attack_Left", false);
			}
			else if (_Rigidbody->GetGround() == false)
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Air_Range_Attack_Right", false);
				else
					_Animator->Play(L"Air_Range_Attack_Left", false);
			}
			else
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Crouch_Range_Attack_Right", false);
				else
					_Animator->Play(L"Crouch_Range_Attack_Left", false);
			}
			break;
		case ePlayerStatus::Crouch:
			if (_Dir == eDir::R)
				_Animator->Play(L"Crouch_Right", false);
			else
				_Animator->Play(L"Crouch_Left", false);
			break;
		case ePlayerStatus::Jump:
			if (_Dir == eDir::R)
				_Animator->Play(L"Jump_Right", false);
			else
				_Animator->Play(L"Jump_Left", false);
			break;
		case ePlayerStatus::Roll:
			if (_Rigidbody->GetGround() == true)
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Roll_Right", false);
				else
					_Animator->Play(L"Roll_Left", false);
			}
			else
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Dash_Right", false);
				else
					_Animator->Play(L"Dash_Left", false);
			}
			break;
		case ePlayerStatus::UseItem:
			if (_Dir == eDir::R)
				_Animator->Play(L"Use_Item_Right", false);
			else
				_Animator->Play(L"Use_Item_Left", false);
			break;
		case ePlayerStatus::Fall:
			if (_Dir == eDir::R)
				_Animator->Play(L"Fall_Right", false);
			else
				_Animator->Play(L"Fall_Left", false);
			break;
		case ePlayerStatus::Hurt:
			if (_Dir == eDir::R)
				_Animator->Play(L"Hurt_Right", false);
			else
				_Animator->Play(L"Hurt_Left", false);
			break;
		case ePlayerStatus::Death:
			if (_Dir == eDir::R)
				_Animator->Play(L"Death_Right", false);
			else
				_Animator->Play(L"Death_Left", false);
			break;
		default:
			break;
		}
	}
	void Kaho_Human::alpha()
	{
		int a = cos(_AlphaDegree*PI/180);
		if (a < 0)
			a *= (-1);
		int alpha = 255 *a;
		_Animator->animationAlpha(alpha);
		if (_AlphaTime > 0.05)
		{
			_AlphaDegree += 90;
			_AlphaTime = 0;
		}
		if (_DamageTime > 2)
		{
			_GetDamage = true;
			_DamageTime = 0;
			_Animator->animationAlpha(255);
		}
	}
	void Kaho_Human::idle()
	{
		if (Input::GetKeyUp(eKeyCode::D))
		{
			_PlayerStatus = ePlayerStatus::Shoot;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			_MoveSpeed = 200.0f;
			_Dir = eDir::R;
			_PlayerStatus = ePlayerStatus::Move;
			animationCtrl();

		}
		if (Input::GetKey(eKeyCode::Left))
		{
			_MoveSpeed = 200.0f;
			_Dir = eDir::L;
			_PlayerStatus = ePlayerStatus::Move;
			animationCtrl();

		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			_IsCrouch = true;
			_PlayerStatus = ePlayerStatus::Crouch;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			_SoundPack[(int)eSound::Jump]->Stop(true);
			_SoundPack[(int)eSound::Jump]->Play(false);
			Vector2 velocity = _Rigidbody->Velocity();
			velocity.y -= _Jumpforce;

			_Rigidbody->Velocity(velocity);
			_Rigidbody->SetGround(false);

			_PlayerStatus = ePlayerStatus::Jump;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			_SoundPack[(int)eSound::Roll]->Play(false);
			_MoveSpeed = 400.0f;
			_PlayerStatus = ePlayerStatus::Roll;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::W))
		{
			_PlayerStatus = ePlayerStatus::UseItem;
			animationCtrl();
		}
		Vector2 velocity = GetComponent<Rigidbody>()->Velocity();
		if (velocity.y > 0)
		{
			_PlayerStatus = ePlayerStatus::Fall;
			animationCtrl();
		}
	}
	void Kaho_Human::move()
	{
		Vector2 velocity = GetComponent<Rigidbody>()->Velocity();
		if (velocity.y > 0)
		{
			_PlayerStatus = ePlayerStatus::Fall;
			animationCtrl();
		}

		//Run_to_Idle
		if (Input::GetKeyUp(eKeyCode::Left)
			|| Input::GetKeyUp(eKeyCode::Right))
		{
			_PlayerStatus = ePlayerStatus::Idle;
			if (_Dir == eDir::R)
				_Animator->Play(L"End_Run_Right", false);
			else
				_Animator->Play(L"End_Run_Left", false);
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			_SoundPack[(int)eSound::Jump]->Stop(true);
			_SoundPack[(int)eSound::Jump]->Play(false);
			_MoveSpeed = 100.0f;
			Vector2 velocity = _Rigidbody->Velocity();
			velocity.y -= _Jumpforce;

			_Rigidbody->Velocity(velocity);
			_Rigidbody->SetGround(false);
			_DoubleJump++;

			_PlayerStatus = ePlayerStatus::Jump;
			animationCtrl();
		}

		//Move pos
		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}

		if (Input::GetKeyDown(eKeyCode::Q))
		{
			_SoundPack[(int)eSound::Roll]->Play(false);
			_MoveSpeed = 400.0f;
			_PlayerStatus = ePlayerStatus::Roll;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::W))
		{
			_PlayerStatus = ePlayerStatus::UseItem;
			animationCtrl();
		}

		if (Input::GetKey(eKeyCode::Left))
		{
			_Dir = eDir::L;
			if (Input::GetKeyDown(eKeyCode::Right))
			{
				_Animator->Play(L"Idle_Left", true);
			}
			else
				animationCtrl();
		}
		else if (Input::GetKey(eKeyCode::Right))
		{
			_Dir = eDir::R;
			if (Input::GetKeyDown(eKeyCode::Left))
			{
				_Animator->Play(L"Idle_Right", true);
			}
			else
				animationCtrl();
		}
		if (_Dir == eDir::L)
			_pos.x -= _MoveSpeed * Time::DeltaTime();
		else if(_Dir == eDir::R)
			_pos.x += _MoveSpeed * Time::DeltaTime();
	}
	void Kaho_Human::attack()
	{
		if (_ComboCount == 1)
		{
			if (_Dir == eDir::L)
				_pos.x -= 30.0f * Time::DeltaTime();
			else if (_Dir == eDir::R)
				_pos.x += 30.0f * Time::DeltaTime();
		}
		else if (_ComboCount == 2)
		{
			if (_Dir == eDir::L)
				_pos.x -= 15.0f * Time::DeltaTime();
			else if (_Dir == eDir::R)
				_pos.x += 15.0f * Time::DeltaTime();
		}
		else if (_ComboCount == 3)
		{
			if (_Dir == eDir::L)
				_pos.x -= 80.0f * Time::DeltaTime();
			else if (_Dir == eDir::R)
				_pos.x += 80.0f * Time::DeltaTime();
		}
		if (_Animator->GetActiveAnim()->IsComplete()==false)
		{
			if (Input::GetKeyDown(eKeyCode::S))
				_Combo = true;
		}
	}
	void Kaho_Human::shoot()
	{
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			_PlayerStatus = ePlayerStatus::Idle;
		}

		if (Input::GetKey(eKeyCode::Down))
		{
			_PlayerStatus = ePlayerStatus::Crouch;
		}
	}
	void Kaho_Human::crouch()
	{
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			if (_Dir == eDir::R)
				_Animator->Play(L"Rise_Right", false);
			else
				_Animator->Play(L"Rise_Left", false);
		}

		if (Input::GetKeyDown(eKeyCode::Down))
		{
			_PlayerStatus=ePlayerStatus::Crouch;
			animationCtrl();
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}


		if (Input::GetKeyDown(eKeyCode::D))
		{
			_PlayerStatus = ePlayerStatus::Shoot;
			animationCtrl();
		}
	}
	void Kaho_Human::jump()
	{

		if (Input::GetKeyDown(eKeyCode::A) && _DoubleJump <= 1)
		{
			_SoundPack[(int)eSound::Jump]->Stop(true);
			_SoundPack[(int)eSound::Jump]->Play(false);
			_DoubleJump++;
			Vector2 velocity = _Rigidbody->Velocity();
			velocity.y = 0;
			velocity.y -= _Jumpforce;

			_Rigidbody->Velocity(velocity);
		}

		if (Input::GetKey(eKeyCode::Left))
		{
			_pos.x -= _MoveSpeed * Time::DeltaTime();
			_Dir = eDir::L;
			animationCtrl();
		}
		else if (Input::GetKey(eKeyCode::Right))
		{
			_pos.x += _MoveSpeed * Time::DeltaTime();
			_Dir = eDir::R;
			animationCtrl();
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			_PlayerStatus = ePlayerStatus::Shoot;
			animationCtrl();
		}

		if (Input::GetKeyDown(eKeyCode::Q) && _DashOn == true)
		{
			_SoundPack[(int)eSound::AirRoll]->Play(false);
			_DashOn = false;
			_CoolTime = 1.5f;
			_MoveSpeed = 1200.0f;
			_PlayerStatus = ePlayerStatus::Roll;
			if (_Dir == eDir::R)
				_Animator->Play(L"PreDash_Right", false);
			else
				_Animator->Play(L"PreDash_Left", false);
		}

		Vector2 velocity = GetComponent<Rigidbody>()->Velocity();
		if (velocity.y > 0)
		{
			_PlayerStatus = ePlayerStatus::Fall;
			animationCtrl();
		}
		if (_Rigidbody->GetGround() == true)
		{
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}
	}
	void Kaho_Human::fall()
	{

		if (Input::GetKeyDown(eKeyCode::A) && _DoubleJump <= 1)
		{
			_SoundPack[(int)eSound::Jump]->Stop(true);
			_SoundPack[(int)eSound::Jump]->Play(false);
			_PlayerStatus = ePlayerStatus::Jump;
			_DoubleJump++;
			Vector2 velocity = _Rigidbody->Velocity();
			velocity.y = 0;
			velocity.y -= _Jumpforce;

			_Rigidbody->Velocity(velocity);
			animationCtrl();
		}

		if (Input::GetKey(eKeyCode::Left))
		{
			_pos.x -= _MoveSpeed * Time::DeltaTime();
			_Dir = eDir::L;
		}
		else if (Input::GetKey(eKeyCode::Right))
		{
			_pos.x += _MoveSpeed * Time::DeltaTime();
			_Dir = eDir::R;
		}

		if (Input::GetKeyDown(eKeyCode::Q) && _DashOn == true)
		{
			_SoundPack[(int)eSound::AirRoll]->Play(false);
			_DashOn = false;
			_CoolTime = 1.5f;
			_MoveSpeed = 1200.0f;
			_PlayerStatus = ePlayerStatus::Roll;
			if (_Dir == eDir::R)
				_Animator->Play(L"PreDash_Right", false);
			else
				_Animator->Play(L"PreDash_Left", false);
		}

		_IsGround = GetComponent<Rigidbody>()->GetGround();

		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}

		if (_IsGround == true)
		{
			_PlayerStatus = ePlayerStatus::Idle;
			if (_Dir == eDir::R)
				_Animator->Play(L"soft_Landing_Right", false);
			else
				_Animator->Play(L"soft_Landing_Left", false);
		}
	}
	void Kaho_Human::roll()
	{
		if (_Rigidbody->GetGround() == true)
		{
			
			if (_Dir == eDir::R)
				_pos.x += _MoveSpeed * Time::DeltaTime();
			else
				_pos.x -= _MoveSpeed * Time::DeltaTime();
		}
		else if(_Rigidbody->GetGround()==false)
		{
			_Rigidbody->Velocity(Vector2(0.0f, 0.0f));
			_DashCharge += Time::DeltaTime();

			if (_DashCharge >= 0.3f)
			{
				if (_Dir == eDir::R)
					_pos.x += _MoveSpeed * Time::DeltaTime();
				else
					_pos.x -= _MoveSpeed * Time::DeltaTime();
			}
		}
	}
	void Kaho_Human::useItem()
	{
		_SoundPack[(int)eSound::UseItem]->Play(false);
		ItemBox* item=nullptr;
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> itemObj = scene->GetGameObject(eLayerType::UI);
		for (auto v : itemObj)
		{
			if (dynamic_cast<ItemBox*>(v))
			{
				item = dynamic_cast<ItemBox*>(v);
			}
		}
		if (item->GetItemNum() == 0)
		{
			_Hp += 30;
			if (_Hp > 100)
				_Hp = 100;
		}
		else
		{
			if(_Switch==false)
				_Switch = true;
		}
	}
	void Kaho_Human::hurt()
	{
		_HurtTime += Time::DeltaTime();
		if (_HurtTime<0.7)
		{
			if (_Dir == eDir::R)
			{
				_pos.x -= 100.0f * Time::DeltaTime();
				_pos.y -= 100.0f * Time::DeltaTime();
			}
			else
			{
				_pos.x += 100.0f * Time::DeltaTime();
				_pos.y -= 100.0f * Time::DeltaTime();
			}
		}
		else
		{
			_HurtTime = 0.0;
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}

	}
	//-------------------------------------------------------------------------------------------------------------------
	//
	//													Events
	// 
	//-------------------------------------------------------------------------------------------------------------------
	void Kaho_Human::attackStart()
	{
		_ComboCount++;
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		_SoundPack[(int)eSound::Attack1]->Play(false);
		MeleeEffect* melee=object::Instantiate<MeleeEffect>(pos, eLayerType::Attack);
		melee->Dir(_Dir);
		melee->attack(1);
		melee->On(_On);
	}
	void Kaho_Human::attackComplete()
	{
		if (Input::GetKey(eKeyCode::Left))
		{
			_Dir = eDir::L;
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			_Dir = eDir::R;
		}
		if (_Combo == true)
		{
			_Combo = false;
			if (_Dir == eDir::R)
				_Animator->Play(L"Melee_Attack_2_Right", false);
			else
				_Animator->Play(L"Melee_Attack_2_Left", false);
		}
		else
		{
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
			_ComboCount = 0;
			_GetDamage = true;
		}
	}
	void Kaho_Human::attackCombo1Start()
	{
		_ComboCount++;
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		_SoundPack[(int)eSound::Attack2]->Play(false);
		MeleeEffect* melee = object::Instantiate<MeleeEffect>(pos, eLayerType::Attack);
		melee->Dir(_Dir);
		melee->attack(2);
		melee->On(_On);
	}
	void Kaho_Human::attackCombo1Complete()
	{
		if (Input::GetKey(eKeyCode::Left))
		{
			_Dir = eDir::L;
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			_Dir = eDir::R;
		}
		if (_Combo == true)
		{
			_Combo = false;
			if (_Dir == eDir::R)
				_Animator->Play(L"Melee_Attack_3_Right", false);
			else
				_Animator->Play(L"Melee_Attack_3_Left", false);
		}
		else
		{
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
			_ComboCount = 0;
			_GetDamage = true;
		}
	}
	void Kaho_Human::attackCombo2Start()
	{
		_ComboCount++;
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		_SoundPack[(int)eSound::Attack3]->Play(false);
		MeleeEffect* melee = object::Instantiate<MeleeEffect>(pos, eLayerType::Attack);
		melee->Dir(_Dir);
		melee->attack(3);
		melee->On(_On);
	}
	void Kaho_Human::attackCombo2Complete()
	{
		if (Input::GetKey(eKeyCode::Left))
		{
			_Dir = eDir::L;
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			_Dir = eDir::R;
		}
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
		_ComboCount = 0;
		_GetDamage = true;
	}
	void Kaho_Human::airAttackStart()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		_SoundPack[(int)eSound::Attack2]->Play(false);
		MeleeEffect* melee = object::Instantiate<MeleeEffect>(pos, eLayerType::Attack);
		melee->Dir(_Dir);
		melee->attack(4);
	}
	void Kaho_Human::airAttackComplete()
	{
		_PlayerStatus = ePlayerStatus::Fall;
		animationCtrl();
	}
	void Kaho_Human::crouchRangeStart()
	{
		_SoundPack[(int)eSound::Shoot]->Play(false);
		Transform* tr = GetComponent<Transform>();
		Arrow* arrow = object::Instantiate<Arrow>(tr->Pos()+Vector2(0.0f,-50.0f), eLayerType::Throws);
		arrow->Dir(_Dir);
	}
	void Kaho_Human::crouchRangeComplete()
	{
		animationCtrl();
	}
	void Kaho_Human::airRangeStart()
	{
		_SoundPack[(int)eSound::Shoot]->Play(false);
		Transform* tr = GetComponent<Transform>();
		Arrow* arrow = object::Instantiate<Arrow>(tr->Pos() + Vector2(0.0f, -30.0f*3), eLayerType::Throws);
		arrow->Dir(_Dir);
	}
	void Kaho_Human::airRangeComplete()
	{
		if (_Rigidbody->GetGround() == false)
			_PlayerStatus = ePlayerStatus::Fall;
		animationCtrl();
	}
	void Kaho_Human::beforeRange()
	{
		_SoundPack[(int)eSound::Shoot]->Play(false);
		Transform* tr = GetComponent<Transform>();
		Arrow* arrow =object::Instantiate<Arrow>(tr->Pos()+Vector2(0.0f,-30.0f*3),eLayerType::Throws);
		arrow->Dir(_Dir);
	}
	void Kaho_Human::afterRange()
	{
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}
	void Kaho_Human::afterRoll()
	{
		_MoveSpeed = 300.0f;
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}
	void Kaho_Human::afterUseItem()
	{
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}
	void Kaho_Human::riseUp()
	{
		_IsCrouch = false;
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}
	void Kaho_Human::endRun()
	{
		animationCtrl();
	}
	void Kaho_Human::landingComplete()
	{
		animationCtrl();
	}
	void Kaho_Human::preDashComplete()
	{
		if (_DashCharge >= 0.2f)
		{
			animationCtrl();
		}
	}
	void Kaho_Human::DashComplete()
	{
		if (_Dir == eDir::R)
			_Animator->Play(L"PostDash_Right", false);
		else
			_Animator->Play(L"PostDash_Left", false);
	}
	void Kaho_Human::postDashComplete()
	{
		_MoveSpeed = 100.0f;
		_PlayerStatus = ePlayerStatus::Fall;
		animationCtrl();
		_DashCharge = 0.0f;
	}
	void Kaho_Human::pray()
	{
		
		if (_PrayEffect == nullptr)
		{
			_SoundPack[(int)eSound::Pray]->Play(false);
			_PrayEffect = object::Instantiate<PrayEffect>(_pos,eLayerType::Effect);
		}
		else
		{
			_PrayEffect->State(eState::Death);
			_PrayEffect = nullptr;
		}
		if (_Hp <= 100)
		{
			_Hp = 100;
		}
	}
	void Kaho_Human::afterpray()
	{
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}
	void Kaho_Human::afterDeath()
	{
		_Hp = 100;
		Transform* tr = GetComponent<Transform>();
		tr->Pos(_RevivalPos);
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
		_Death = false;
	}
	void Kaho_Human::walkSound()
	{
		_SoundPack[(int)eSound::Walk]->Play(false);
	}
}