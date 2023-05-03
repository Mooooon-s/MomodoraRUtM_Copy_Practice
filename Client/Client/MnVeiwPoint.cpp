#include "MnVeiwPoint.h"
#include "MnTransform.h"
#include "MnComponent.h"
#include "MnSceneManager.h"
#include "MnKaho.h"
#include "MnGround.h"
#include "MnImage.h"
namespace Mn
{
	VeiwPoint::VeiwPoint()
		: GameObject()
		, _Kaho(nullptr)
		, _Image(nullptr)
		, _Ground(nullptr)
		, _PlayerPos(Vector2::Zero)
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(480,360));
		_Pos = tr->Pos();
	}
	VeiwPoint::~VeiwPoint()
	{
	}
	void VeiwPoint::Initialize()
	{
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> playerobj = scene->GetGameObject(eLayerType::Player);
		for (auto v : playerobj)
		{
			if (dynamic_cast<Kaho*>(v))
				_Kaho = dynamic_cast<Kaho*>(v);
		}
		std::vector<GameObject*> Groundobj = scene->GetGameObject(eLayerType::Ground);
		for (auto v : Groundobj)
		{
			if (dynamic_cast<Ground*>(v))
				_Ground = dynamic_cast<Ground*>(v);
		}
		_Image = _Ground->Map();
		GameObject::Initialize();
	}
	void VeiwPoint::Update()
	{
		Transform* tr = GetComponent<Transform>();
		_PlayerPos = _Kaho->GetComponent<Transform>()->Pos();
		if (_PlayerPos.x > 480 && _PlayerPos.x < (_Image->Width()-480))
			_Pos.x = _PlayerPos.x;
		if (_PlayerPos.y > 360 && _PlayerPos.y < (_Image->Height() - 360))
			_Pos.y = _PlayerPos.y;
		if (_PlayerPos.x < 480)
			_Pos.x = 480;
		if (_PlayerPos.y < 360)
			_Pos.y =360;
		if (_PlayerPos.y > (_Image->Height() - 360))
			_Pos.y = _Image->Height() - 360;
		tr->Pos(_Pos);
	}
	void VeiwPoint::Release()
	{
	}
}