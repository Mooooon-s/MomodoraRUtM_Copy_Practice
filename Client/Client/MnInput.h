#pragma once
#include "MnEngine.h"

namespace Mn {

	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		END,
	};

	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};

	class Input
	{
	public:
		struct Key {
			eKeyCode	key;
			eKeyState	state;
			bool		bPressed;
		};
		static void Initialize();
		static void Updatae();
		static void Render(HDC hdc);
	public:
		inline static eKeyState GetKeyState(eKeyCode keyCode) 
		{
			return _Keys[(UINT)keyCode].state;
		}

	private:
		static std::vector<Key> _Keys;
	};
}