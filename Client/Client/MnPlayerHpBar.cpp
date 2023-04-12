#include "MnPlayerHpBar.h"
#include "MnResources.h"
#include "MnComponent.h"
#include "MnTransform.h"
#include "MnImage.h"
namespace Mn
{
	PlayerHpBar::PlayerHpBar()
		: _HpBarFrame(nullptr)
		, _Animator(nullptr)
		, _HpBar(nullptr)
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
	}
	void PlayerHpBar::Update()
	{
	}
	void PlayerHpBar::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		TransparentBlt(hdc, pos.x, pos.y, _HpBarFrame->Width(), _HpBarFrame->Height()
			, _HpBarFrame->Hdc(),0,0, _HpBarFrame->Width(), _HpBarFrame->Height(), RGB(0, 128, 128));
		TransparentBlt(hdc, pos.x+3, pos.y+3, _HpBar->Width(), _HpBar->Height()
			, _HpBar->Hdc(), 0, 0, _HpBar->Width(), _HpBar->Height(), RGB(0, 128, 128));
	}
	void PlayerHpBar::Release()
	{
	}
}