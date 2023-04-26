#include "MnBossHpBar.h"
#include "MnImage.h"
#include "MnResources.h"
#include "MnComponent.h"
#include "MnTransform.h"
namespace Mn
{
	BossHpBar::BossHpBar()
		: GameObject()
		, _Frame(nullptr)
		, _Bar(nullptr)
		, _Hp(100)
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(150, 650));
	}
	BossHpBar::~BossHpBar()
	{
	}
	void BossHpBar::Initialize()
	{
		SetName(L"BossHpBar");
		_Frame = Resources::Load<Image>(L"BossHpBarFrame", L"..\\Resources\\BossHpBarFram.bmp");
		_Bar = Resources::Load<Image>(L"BossHpBar", L"..\\Resources\\BossHpBar.bmp");
		GameObject::Initialize();
	}
	void BossHpBar::Update()
	{
		GameObject::Update();
	}
	void BossHpBar::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		TransparentBlt(hdc, pos.x, pos.y, _Frame->Width()*3, _Frame->Height()*3, _Frame->Hdc(), 0, 0, _Frame->Width(), _Frame->Height(), RGB(0, 128, 128));
		TransparentBlt(hdc, pos.x, pos.y+6, _Bar->Width()*3*(_Hp/100), _Bar->Height()*3, _Bar->Hdc(), 0, 0, _Bar->Width(), _Bar->Height(), RGB(0, 128, 128));
		GameObject::Render(hdc);
	}
	void BossHpBar::Release()
	{
		GameObject::Release();
	}
}