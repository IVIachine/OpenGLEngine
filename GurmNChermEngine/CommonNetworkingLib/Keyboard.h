#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <SFML/Graphics.hpp>
#include <cassert>

#define KEYBOARD Keyboard::getInstance()

class Input;

class Keyboard
{
public:
	enum Keys : int
	{
		Unknown = -1,
		A = 0,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Escape,
		LControl,
		LShift,
		LAlt,
		LSystem,
		RControl,
		RShift,
		RAlt,
		RSystem,
		Menu,
		LBracket,
		RBracket,
		SemiColon,
		Comma,
		Period,
		Quote,
		Slash,
		BackSlash,
		Tilde,
		Equal,
		Dash,
		Space,
		Return,
		BackSpace,
		Tab,
		PageUp,
		PageDown,
		End,
		Home,
		Insert,
		Delete,
		Add,
		Subtract,
		Multiply,
		Divide,
		Left,
		Right,
		Up,
		Down,
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		Pause,
		KeyCount
	};

	struct KeyState
	{
		bool
			mStateNew[Keys::KeyCount],
			mStateOld[Keys::KeyCount];

		KeyState()
		{
			for (int i = 0; i < Keys::KeyCount; i++)
			{
				mStateNew[i] = false;
				mStateOld[i] = false;
			}
		}

		KeyState(const KeyState& copy)
		{
			for (int i = 0; i < Keys::KeyCount; i++)
			{
				mStateNew[i] = copy.mStateNew[i];
				mStateOld[i] = copy.mStateOld[i];
			}
		}

		~KeyState()
		{

		}

		static void beginStep(KeyState& state)
		{
			for (int i = 0; i < Keys::KeyCount; i++)
			{
				state.mStateNew[i] = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
			}
		}

		static void endStep(KeyState& state)
		{
			for (int i = 0; i < Keys::KeyCount; i++)
			{
				state.mStateOld[i] = state.mStateNew[i];
			}
		}
	};

private:
	Keyboard();
	~Keyboard();

	static Keyboard*	getInstance();
	static void			destroyInstance();
	static Keyboard*	createInstance();

	void beginStep();
	void endStep();

	bool getKey(Keys key);
	bool getKeyDown(Keys key);
	bool getKeyUp(Keys key);

	bool isNew(Keys key);
	bool isOld(Keys key);

	KeyState m_keysNew;
	KeyState m_keysOld;

	static Keyboard* sp_instance;

	friend class Input;
};

#endif