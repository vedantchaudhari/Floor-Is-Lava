/*
	EGP Networking: Plugin Configuration
	Dan Buckstein
	October 2018

	Utility for configuring library symbol exports and imports.
*/

#ifndef _EGP_NET_PLUGIN_CONFIG_H_
#define _EGP_NET_PLUGIN_CONFIG_H_


#ifdef EGP_NET_DLLEXPORT
// compiler logic for DLL-producing project
// e.g. the plugin itself

#else	// !EGP_NET_DLLEXPORT
#ifdef EGP_NET_DLLIMPORT
// compiler logic for DLL-consuming project
// e.g. Unity game; test app

#else	// !EGP_NET_DLLIMPORT
// compiler logic for DLL-unrelated project
// e.g. static code project

#endif	// EGP_NET_DLLIMPORT
#endif	// EGP_NET_DLLEXPORT


#endif	// !_EGP_NET_PLUGIN_CONFIG_H_