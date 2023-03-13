#include "MnMainMenuBG.h"
#include "MnResources.h"
#include "MnCamera.h"
#include "MnTransform.h"
namespace Mn
{
	MainMenuBG::MainMenuBG()
		:_Image(NULL)
	{
	}
	MainMenuBG::~MainMenuBG()
	{
	}
	void MainMenuBG::Initialize()
	{
		_Image = Resources::Load<Image>(L"MainMenuBG", L"..\\Resources\\MainMenu.bmp");
		GameObject::Initialize();
	}
	void MainMenuBG::Update()
	{
		GameObject::Update();
	}
	void MainMenuBG::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Camera::ComputePos(tr->Pos());
		BitBlt(hdc, 0, 0, _Image->Width(), _Image->Height(), _Image->Hdc(), 0, 0, SRCCOPY);
		GameObject::Render(hdc);
	}
}