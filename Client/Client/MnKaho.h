#pragma once
#include "MnGameObject.h"
#include "MnPlayerEnum.h"

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

