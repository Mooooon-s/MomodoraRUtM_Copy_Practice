#pragma once
#include "MnEngine.h"

namespace Mn {

	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M
		,Left,Up,Right,Down,
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

		static __forceinline bool GetKey(eKeyCode keyCode)
		{
			return _Keys[static_cast<UINT>(keyCode)].state == eKeyState::Pressed;
		}

		static __forceinline bool GetKeyDown(eKeyCode keyCode)
		{
			return _Keys[static_cast<UINT>(keyCode)].state == eKeyState::Down;
		}

		static __forceinline bool GetKeyUp(eKeyCode keyCode)
		{
			return _Keys[static_cast<UINT>(keyCode)].state == eKeyState::Up;
		}

	private:
		static std::vector<Key> _Keys;
	};
}