#include "MnInput.h"

namespace Mn
{
	int ASCII[(UINT)eKeyCode::END] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		37,38,39,40
	};


	std::vector<Input::Key> Input::_Keys;


	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++) 
		{
			Key keyinfo;
			keyinfo.key = (eKeyCode)i;
			keyinfo.state = eKeyState::None;
			keyinfo.bPressed = false;

			_Keys.push_back(keyinfo);
		}
	}
	void Input::Updatae()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++) 
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000) 
			{
				if (_Keys[i].bPressed)
					_Keys[i].state = eKeyState::Pressed;
				else
					_Keys[i].state = eKeyState::Down;

				_Keys[i].bPressed = true;
			}
			else
			{
				if(_Keys[i].bPressed)
					_Keys[i].state = eKeyState::Up;
				else
					_Keys[i].state = eKeyState::None;
				_Keys[i].bPressed = false;
			}
		}
	}

	void Input::Render(HDC hdc)
	{
	}
}
