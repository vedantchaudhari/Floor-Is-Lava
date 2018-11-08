/*
	egpInput.h
	By Dan Buckstein (c) 2017

	Simple input tracking.
*/

#ifndef __EGP_INPUT_H_
#define __EGP_INPUT_H_


#ifdef __cplusplus
extern "C"
{
#else
typedef struct egpKeyboard	egpKeyboard;
typedef struct egpTimer		egpMouse;
#endif	// __cplusplus


//-----------------------------------------------------------------------------

// simple keyboard state tracking structure
struct egpKeyboard
{
	struct {
		unsigned char key[256];
		unsigned char special[256];
	} state, state0;
};


// simple mouse state tracking structure
struct egpMouse
{
	struct {
		unsigned char btn[8];
		int x, y, wheel;
	} state, state0;
	int dx, dy, dwheel;
};


//-----------------------------------------------------------------------------

// check keyboard states and changes
// all return 1 if true, 0 if false, -1 if invalid params
int egpKeyboardKeyIsDown(const egpKeyboard *keyboard, unsigned char key);
int egpKeyboardKeyIsUp(const egpKeyboard *keyboard, unsigned char key);
int egpKeyboardKeyWasPressed(const egpKeyboard *keyboard, unsigned char key);
int egpKeyboardKeyWasReleased(const egpKeyboard *keyboard, unsigned char key);

// check mouse states and changes
// all return 1 if true, 0 if false, -1 if invalid params
int egpMouseButtonIsDown(const egpMouse *mouse, unsigned char button);
int egpMouseButtonIsUp(const egpMouse *mouse, unsigned char button);
int egpMouseButtonWasPressed(const egpMouse *mouse, unsigned char button);
int egpMouseButtonWasReleased(const egpMouse *mouse, unsigned char button);

// update input trackers
// all return 1 if success, -1 if invalid params
int egpKeyboardUpdate(egpKeyboard *keyboard);
int egpMouseUpdate(egpMouse *mouse);

int egpKeyboardReset(egpKeyboard *keyboard);
int egpMouseReset(egpMouse *mouse);

int egpKeyboardCopyState(egpKeyboard *keyboard, const egpKeyboard *copy);
int egpMouseCopyState(egpMouse *mouse, const egpMouse *copy);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#include "_inl/egpInput.inl"


#endif	// !__EGP_INPUT_H_