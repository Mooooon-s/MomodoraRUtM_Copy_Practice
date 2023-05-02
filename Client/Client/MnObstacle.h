#pragma once
#include "MnGameObject.h"
#include "MnMapTrriger.h"
namespace Mn
{
	class Image;
	class Sound;
	class Animator;
	class Collider;
	class Rigidbody;
	class Obstacle : public GameObject
	{
	private:
		enum class eObstacleState
		{
			Search,
			Trigg,
			Done,
		};
		Image*			_Image;
		Image*			_Ground;
		Sound*			_Sound;
		Collider*		_Collider;
		Animator*		_Animator;
		Rigidbody*		_Rigidbody;
		MapTrriger*		_Trigger;
		eObstacleState	_ObState;
	public:
		Obstacle();
		~Obstacle();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnCollisionEnter(class Collider* other) override;
	private:
		void search();
		void done();
		void trigg();

	};
}

