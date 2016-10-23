#ifndef _MOUSE_STATE_H_
#define _MOUSE_STATE_H_


#include <cassert>

#define MOUSE Mouse::getInstance()

class Input;

class Mouse
{
public:
	enum Buttons : int
	{
		Unknown = -1,
		Left,
		Right,
		Middle,
		ButtonCount
	};

	struct MouseState
	{
		bool
			mStateOld[Buttons::ButtonCount],
			mStateNew[Buttons::ButtonCount];

		MouseState()
		{
			for (int i = 0; i < Buttons::ButtonCount; i++)
			{
				mStateNew[i] = false;
				mStateOld[i] = false;
			}
		}

		MouseState(const MouseState& copy)
		{
			for (int i = 0; i < Buttons::ButtonCount; i++)
			{
				mStateNew[i] = copy.mStateNew[i];
				mStateOld[i] = copy.mStateOld[i];
			}
		}

		~MouseState()
		{

		}

		static void beginStep(MouseState& state)
		{
			//state.mStateNew[Buttons::Left] = sf::Mouse::isButtonPressed(sf::Mouse::Left);
			//state.mStateNew[Buttons::Right] = sf::Mouse::isButtonPressed(sf::Mouse::Right);
			//state.mStateNew[Buttons::Middle] = sf::Mouse::isButtonPressed(sf::Mouse::Middle);
		}

		static void endStep(MouseState& state)
		{
			state.mStateOld[Buttons::Left] = state.mStateNew[Buttons::Left];
			state.mStateOld[Buttons::Right] = state.mStateNew[Buttons::Right];
			state.mStateOld[Buttons::Middle] = state.mStateNew[Buttons::Middle];
		}
	};

private:
	Mouse();
	~Mouse();

	static Mouse*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static Mouse*	createInstance()
	{
		sp_instance = new Mouse();
		return getInstance();
	};
	static void		destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	void beginStep();
	void endStep();

	bool getButton(Buttons button);
	bool getButtonDown(Buttons button);
	bool getButtonUp(Buttons button);

	bool isNew(Buttons button);
	bool isOld(Buttons button);

	MouseState m_mouseNew;
	MouseState m_mouseOld;

	static Mouse* sp_instance;

	friend class Input;
};

#endif