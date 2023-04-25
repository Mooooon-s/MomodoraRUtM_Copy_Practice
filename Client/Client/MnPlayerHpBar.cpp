#include "MnPlayerHpBar.h"
#include "MnResources.h"
#include "MnComponent.h"
#include "MnTransform.h"
#include "MnImage.h"
#include "MnSceneManager.h"
#include "MnKaho.h"
namespace Mn
{
	PlayerHpBar::PlayerHpBar()
		: _HpBarFrame(nullptr)
		, _Kaho(nullptr)
		, _HpBar(nullptr)
		, _Hp(100)
	{
	}
	PlayerHpBar::~PlayerHpBar()
	{
	}
	void PlayerHpBar::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(100.0f, 50.0f));
		_HpBarFrame = Resources::Load<Image>(L"PlayerHpBarFrame",L"..\\Resources\\PlayerHpBarFrame.bmp");
		_HpBar = Resources::Load<Image>(L"PlayerHpBar", L"..\\Resources\\PlayerHpBar.bmp");
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> playerObj = scene->GetGameObject(eLayerType::Player);
		for (auto v : playerObj)
		{
			if (dynamic_cast<Kaho*>(v))
			{
				_Kaho = dynamic_cast<Kaho*>(v);
				break;
			}
		}
		GameObject::Initialize();
	}
	void PlayerHpBar::Update()
	{
		_Hp = _Kaho->HP();
		GameObject::Update();
	}
	void PlayerHpBar::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		TransparentBlt(hdc, pos.x, pos.y, _HpBarFrame->Width(), _HpBarFrame->Height()
			, _HpBarFrame->Hdc(),0,0, _HpBarFrame->Width(), _HpBarFrame->Height(), RGB(0, 128, 128));
		TransparentBlt(hdc, pos.x+3, pos.y+3, _HpBar->Width()*(_Hp/100), _HpBar->Height()
			, _HpBar->Hdc(), 0, 0, _HpBar->Width(), _HpBar->Height(), RGB(0, 128, 128));
	}
	void PlayerHpBar::Release()
	{
	}
}