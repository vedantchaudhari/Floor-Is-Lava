/*
	EGP Networking: Plugin Test
	Dan Buckstein
	October 2018

	Developer's test application for plugin for Unity.
*/

// include the plugin interface file to take the "easy route"
#include "../egp-net-plugin-Unity/egp-net-plugin.h"


// macro for name of plugin
#define PLUGIN_NAME "egp-net-plugin-Unity"


#ifdef _EGP_NET_PLUGIN_H_
// included plugin interface
// link static version of plugin
#pragma comment(lib,PLUGIN_NAME".lib")
#else
// no knowledge of functions in plugin
// the goal of this project is to "fake" what the plugin should do
// therefore, we need to load it and consume it like Unity will
#include <Windows.h>
#endif	// _EGP_NET_PLUGIN_H_


int main(int const argc, char const *const *const argv)
{
#ifndef _EGP_NET_PLUGIN_H_
	// consume library
	HMODULE library = LoadLibrary(PLUGIN_NAME".dll");
	if (library)
	{
		// load and test functions from library

#endif	// !_EGP_NET_PLUGIN_H_



#ifndef _EGP_NET_PLUGIN_H_
		// release library
		FreeLibrary(library);
	}
#endif	// !_EGP_NET_PLUGIN_H_
}
