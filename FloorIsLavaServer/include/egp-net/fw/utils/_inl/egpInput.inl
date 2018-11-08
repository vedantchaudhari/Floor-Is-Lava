/*
	egpInput.inl
	By Dan Buckstein (c) 2017

	Simple input tracking.
*/

#ifdef __EGP_INPUT_H_
#ifndef __EGP_INPUT_INL_
#define __EGP_INPUT_INL_


// check keyboard states and changes
inline int egpKeyboardKeyIsDown(const egpKeyboard *keyboard, unsigned char key)
{
	if (keyboard)
		return (keyboard->state.key[key]);
	return -1;
}

inline int egpKeyboardKeyIsUp(const egpKeyboard *keyboard, unsigned char key)
{
	if (keyboard)
		return (!keyboard->state.key[key]);
	return -1;
}

inline int egpKeyboardKeyWasPressed(const egpKeyboard *keyboard, unsigned char key)
{
	if (keyboard)
		return (keyboard->state.key[key] && !keyboard->state0.key[key]);
	return -1;
}

inline int egpKeyboardKeyWasReleased(const egpKeyboard *keyboard, unsigned char key)
{
	if (keyboard)
		return (!keyboard->state.key[key] && keyboard->state0.key[key]);
	return -1;
}


// check mouse states and changes
inline int egpMouseButtonIsDown(const egpMouse *mouse, unsigned char button)
{
	if (mouse)
		return (mouse->state.btn[button]);
	return -1;
}

inline int egpMouseButtonIsUp(const egpMouse *mouse, unsigned char button)
{
	if (mouse)
		return (!mouse->state.btn[button]);
	return -1;
}

inline int egpMouseButtonWasPressed(const egpMouse *mouse, unsigned char button)
{
	if (mouse)
		return (mouse->state.btn[button] && !mouse->state0.btn[button]);
	return -1;
}

inline int egpMouseButtonWasReleased(const egpMouse *mouse, unsigned char button)
{
	if (mouse)
		return (!mouse->state.btn[button] && mouse->state0.btn[button]);
	return -1;
}


// update input trackers
inline int egpKeyboardUpdate(egpKeyboard *keyboard)
{
	if (keyboard)
	{
		keyboard->state0 = keyboard->state;
		return 1;
	}
	return -1;
}

inline int egpMouseUpdate(egpMouse *mouse)
{
	if (mouse)
	{
		mouse->state0 = mouse->state;
		return 1;
	}
	return -1;
}


inline int egpKeyboardReset(egpKeyboard *keyboard)
{
	if (keyboard)
	{
		const egpKeyboard result = { 0 };
		*keyboard = result;
		return 1;
	}
	return -1;
}

inline int egpMouseReset(egpMouse *mouse)
{
	if (mouse)
	{
		const egpMouse result = { 0 };
		*mouse = result;
		return 1;
	}
	return -1;
}


inline int egpKeyboardCopyState(egpKeyboard *keyboard, const egpKeyboard *copy)
{
	if (keyboard && copy)
	{
		keyboard->state = copy->state;
		return 1;
	}
	return -1;
}

inline int egpMouseCopyState(egpMouse *mouse, const egpMouse *copy)
{
	if (mouse && copy)
	{
		mouse->state = copy->state;
		return 1;
	}
	return -1;
}


#endif	// !__EGP_INPUT_INL_
#endif	// __EGP_INPUT_H_