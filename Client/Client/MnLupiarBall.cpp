#include "MnLupiarBall.h"
#include "MnImage.h"
#include "MnResources.h"
#include "MnComponent.h"
#include "MnTransform.h"
#include "MnRigidbody.h"
#include "MnCollider.h"
#include "MnTime.h"
namespace Mn
{
	LupiarBall::LupiarBall()
		: GameObject()
		, _Image(nullptr)
		, _Collider(nullptr)
		, _Rigidbody(nullptr)
		, _Timer(0.0f)
		, _DirVec(Vector2::Zero)
	{
		Transform* Tr = GetComponent<Transform>();
		Tr->Pos(Vector2(-200, -200));
	}
	LupiarBall::~LupiarBall()
	{
	}
	void LupiarBall::Initialize()
	{
		SetName(L"Throws");
		_Image = Resources::Load<Image>(L"LupiarBall", L"..\\Resources\\Lupiar_Ball_Alpha.bmp");
		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(false);

		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2((_Image->Width() / 5)*2, _Image->Height()*2));
		for (int i = 0; i <= 9; i++)
		{
			Fpos.push_back(Vector2(-200,-200));
		}
		Vector2 velocity = _Rigidbody->Velocity();
		velocity.y -= 800.0f;
		_Rigidbody->Velocity(velocity);
		GameObject::Initialize();
	}
	void LupiarBall::Update()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		_Timer += Time::DeltaTime();
		if (_Timer >= 0.05)
		{
			for (int i = 0; i < 9; i++)
			{
				if (Fpos[i] != Fpos[i + 1])
				{
					Fpos[i] = Fpos[i + 1];
				}
			}
			_Timer = 0;
		}
		_Rigidbody->AddForce(Vector2(_DirVec.x*-1,0.0f) * 200.0f);
		Tr->Pos(pos);
		Fpos[9] = Tr->Pos();
		GameObject::Update();
	}
	void LupiarBall::Render(HDC hdc)
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;
		AlphaBlend(hdc, Fpos[9].x, Fpos[9].y, ((_Image->Width() / 5) * 2), _Image->Height()*2, _Image->Hdc(), 0, 0, _Image->Width() / 5, _Image->Height(), func);
		AlphaBlend(hdc, Fpos[8].x, Fpos[8].y, ((_Image->Width() / 5) * 2), _Image->Height()*2, _Image->Hdc(), 0, 0, _Image->Width() / 5, _Image->Height(), func);
		func.SourceConstantAlpha = 127;
		AlphaBlend(hdc, Fpos[7].x, Fpos[7].y, ((_Image->Width() / 5)*2), _Image->Height()*2, _Image->Hdc(), 24, 0, _Image->Width() / 5, _Image->Height(), func);
		AlphaBlend(hdc, Fpos[6].x, Fpos[6].y, ((_Image->Width() / 5)*2), _Image->Height()*2, _Image->Hdc(), 24, 0, _Image->Width() / 5, _Image->Height(), func);
		func.SourceConstantAlpha = 63;
		AlphaBlend(hdc, Fpos[5].x, Fpos[5].y, ((_Image->Width() / 5)*2), _Image->Height()*2, _Image->Hdc(), 24 * 2, 0, _Image->Width() / 5, _Image->Height(), func);
		AlphaBlend(hdc, Fpos[4].x, Fpos[4].y, ((_Image->Width() / 5)*2), _Image->Height()*2, _Image->Hdc(), 24 * 2, 0, _Image->Width() / 5, _Image->Height(), func);
		AlphaBlend(hdc, Fpos[3].x, Fpos[3].y, ((_Image->Width() / 5)*2), _Image->Height()*2, _Image->Hdc(), 24 * 3, 0, _Image->Width() / 5, _Image->Height(), func);
		AlphaBlend(hdc, Fpos[2].x, Fpos[2].y, ((_Image->Width() / 5)*2), _Image->Height()*2, _Image->Hdc(), 24 * 3, 0, _Image->Width() / 5, _Image->Height(), func);
		AlphaBlend(hdc, Fpos[1].x, Fpos[1].y, ((_Image->Width() / 5)*2), _Image->Height()*2, _Image->Hdc(), 24 * 4, 0, _Image->Width() / 5, _Image->Height(), func);
		AlphaBlend(hdc, Fpos[0].x, Fpos[0].y, ((_Image->Width() / 5)*2), _Image->Height()*2, _Image->Hdc(), 24 * 4, 0, _Image->Width() / 5, _Image->Height(), func);
		GameObject::Render(hdc);
	}
	void LupiarBall::Release()
	{
		GameObject::Release();
	}
	void LupiarBall::OnCollisionEnter(Collider* other)
	{
	}
	void LupiarBall::StartPos(Vector2 pos)
	{
		for (auto v : Fpos) 
		{
			v = pos;
		}
	}
}