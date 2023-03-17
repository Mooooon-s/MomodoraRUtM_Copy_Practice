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
		Vector2			_Pos;
		bool			_bIsCat;
		Kaho_Cat*		kahoCat;
		Kaho_Human*		kahoHuman;
		Collider*		_KahoColl;
		eDir			_Dir;
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
	};
}

