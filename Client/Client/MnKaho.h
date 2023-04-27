#pragma once
#include "MnGameObject.h"
#include "MnPlayerEnum.h"
#include "MnSceneManager.h"

namespace Mn
{
	class Kaho_Cat;
	class Kaho_Human;
	class Collider;
	class Kaho : public GameObject
	{
	private:
		Kaho_Human*		kahoHuman;
		Kaho_Cat*		kahoCat;
		Vector2			_Pos;
		eDir			_Dir;
		bool			_bIsCat;
		bool			_Swap;
		float			_Hp;
		eSceneType		_Scene;
		Vector2			_RevivalPos;
	public:
		Kaho();
		~Kaho();
	public:
		void Initialize()override;
		void Update()override;
		void Render(HDC hdc)override;
		void Release() override;
	public:
		void  UpdateStatus();
		const Vector2 KahoPos() { return _Pos; }
		const Vector2 KahoPos(Vector2 pos) { _Pos = pos; }
		bool IsCat() { return _bIsCat; }
		void IsCat(bool iscat) { _bIsCat = iscat; }
		float HP() { return _Hp; }
		void HP(float hp) { _Hp = hp; }
		void SceneType(eSceneType scene) { _Scene = scene; }
		eSceneType SceneType() { return _Scene; }
		void Revival(Vector2 pos) { _RevivalPos = pos; }
		Vector2 Revival() { return _RevivalPos; }
	public:
		int KahoDir();
		Vector2 KahoColliderSize();
	public:
		void GetCatHunam(Kaho_Cat* c, Kaho_Human* h) 
		{ 
			kahoCat = c; 
			kahoHuman = h; 
		}
		template<typename T>
		T* CameraTarget()
		{
			if (_bIsCat)
				return dynamic_cast<T*>(kahoCat);
			else
				return dynamic_cast<T*>(kahoHuman);
		}
		template<typename T>
		T* GetRigidbody()
		{
			if (_bIsCat)
				return dynamic_cast<T*>(kahoCat);
			else
				return dynamic_cast<T*>(kahoHuman);
		}
	};
}

