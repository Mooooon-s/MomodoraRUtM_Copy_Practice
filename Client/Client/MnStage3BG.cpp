#include "MnStage3BG.h"
#include "MnResources.h"
#include "MnSceneManager.h"
#include "MnImage.h"
namespace Mn
{
	Stage3BG::Stage3BG()
		: GameObject()
		, _Image(nullptr)
	{
	}
	Stage3BG::~Stage3BG()
	{
	}
	void Stage3BG::Initialize()
	{
		Scene* scene = SceneManager::ActiveScene();
		if (scene->GetName() == L"Stage3_1")
			_Image = Resources::Load<Image>(L"Stage3_1", L"..\\Resources\\Stage3_BackGround_1.bmp");
		if (scene->GetName() == L"Stage3_2")
			_Image = Resources::Load<Image>(L"Stage3_2", L"..\\Resources\\Stage3_BackGround_2.bmp");
		if (scene->GetName() == L"Stage3_3")
			_Image = Resources::Load<Image>(L"Stage3_3", L"..\\Resources\\Stage3_BackGround_3.bmp");
		GameObject::Initialize();
	}
	void Stage3BG::Update()
	{
	}
	void Stage3BG::Render(HDC hdc)
	{
		BitBlt(hdc, 0, 0, _Image->Width(), _Image->Height(), _Image->Hdc(), 0, 0, SRCCOPY);
		GameObject::Render(hdc);
	}
}